
/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float3 norw : NORMAL0;
    float2 texture_pos : TEXCOORD0;
    float3 light : LIGHT0;
    float3 eye_vec : EYE0;
    float4 light_tex_coord : TEXCOORD1;
    float4 light_view_pos : LIGHT_VIEW_POS0;
};

/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //! ワールド行列
    float4x4 View; //! ビュー行列
    float4x4 Projection; //! プロジェクション行列
    float4x4 LightView; //! ライトから見たビュー行列
    float4x4 LightProjection; //! ライトから見たプロジェクション行列
    float4x4 ClipUV; //! UV変換用行列
    float4 CameraPos; //! カメラ座標
    float4 Light; //! ライトの方向
    float4 MaterialAmbient; //! アンビエント光
    float4 MaterialDiffuse; //! ディヒューズ光
    float4 MaterialSpecular; //! スペキュラー光
};

/****************************************
          テクスチャ
****************************************/

Texture2D    Texture        : register(t0);
SamplerState Sampler        : register(s0);
Texture2D    TextureDepth   : register(t1);
SamplerState ShadowSampler : register(s1);


/****************************************
          共通関数
****************************************/

float HalfLambert(float3 lig_dir, float3 normal)
{
    float ndl = saturate(dot(normal, lig_dir));
    
    float half_ndl = ndl * 0.5 + 0.5;
    float square_ndl = half_ndl * half_ndl;
	
    return square_ndl;
}

float4 Phong(float3 normal, float3 eye_vec, float3 lig_dir)
{
    // ライトの反射ベクトルを求める
    float ndl = saturate(dot(normal, lig_dir));
    float3 ref_vec = normalize(-lig_dir + 2.0 * normal * ndl);
    
    // 鏡面反射の強さを算出
    float t = saturate(dot(ref_vec, eye_vec));
    
    // 強さを絞る
    t = pow(t, 60.0);
    
    return t;
}
/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{    
    // 上向きの単位ベクトル
    float3 up_n = float3(0.0, 1.0, 0.0);
    // 上向きのベクトルと法線の内積を行う
    float v_d_n = saturate(dot(up_n, input.norw));
    
    // 茶
    float3 brown = float3(0.45, 0.31, 0.18);
    // 緑
    float3 green = float3(0.54, 0.67, 0.22);

    /*
        今回の場合、内積の結果は
        斜面に近いほど[0.0]になる
        平面に近いほど[1.0]になる
        その補間値に使用することで、
        平面では、[緑]
        斜面では、[茶]
        になる。
    */
    float3 diffuse = lerp(brown, green, v_d_n);
    
    // 反射率を求める
    float t = HalfLambert(Light.xyz, input.norw);
    diffuse *= t;  
   
    // 環境光
    float3 ambient = diffuse / 2.0;
    
    // スペキュラーカラー
    float3 specular = Phong(input.norw, input.eye_vec, Light.xyz);
   
    float3 color = ambient + diffuse + specular;
    
    // スクリーンの横幅
    float SCREEN_WIDTH  = 1280.0;
    // スクリーンの縦幅
    float SCREEN_HEIGHT = 720.0;
    // ずらすピクセル数
    float OFFSET_PIXEL  = 1.0;
    
    // 影
    float2 sm_uv = input.light_tex_coord.xy / input.light_tex_coord.w;
    if (sm_uv.x >= 0.0 && sm_uv.x <= 1.0
        && sm_uv.y >= 0.0 && sm_uv.y <= 1.0)
    {   
        // シャドウアクネ対策でバイアスを掛ける
        float bias = 0.0003;
        
        // 今回のライトから見た深度値を算出
        float z_light_view = input.light_view_pos.z;
        
        // ピクセルのオフセット値を計算
        float offset_u = OFFSET_PIXEL / SCREEN_WIDTH;
        float offset_v = OFFSET_PIXEL / SCREEN_HEIGHT;
        
        // 基準となるテクセル含む近くのテクセルをサンプリングする
        float z_shadow_map_0 = TextureDepth.Sample(ShadowSampler, sm_uv).r;                                                    
        float z_shadow_map_1 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u,      0.0)).r;
        float z_shadow_map_2 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(offset_u, offset_v)).r;
        float z_shadow_map_3 = TextureDepth.Sample(ShadowSampler, sm_uv + float2(     0.0, offset_v)).r;
        
        // シャドウマップに保存されている深度値よりも長い場合、影になるので射影率を 1 加算する        
        float shadow_rate = 0.0;
        if (z_light_view > z_shadow_map_0 + bias){
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_1 + bias){
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_2 + bias){
            shadow_rate += 1.0;
        }
        if (z_light_view > z_shadow_map_3 + bias){
            shadow_rate += 1.0;
        }
        // 射影率の平均を求める 0 ～ 1 (0% ～ 100%)になる
        shadow_rate /= 4.0;
        
        // 線形補間で射影率に応じて色を滑らかに変化させる
        float3 shadow_color = color / 3.0;
        color = lerp(color, shadow_color, shadow_rate);
    }
    
    return float4(color, 1.0);
}