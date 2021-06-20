
/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos              : SV_POSITION;
    float4 posw             : POSITION0;
    float3 norw             : NORMAL0;
    float2 texture_pos      : TEXCOORD0;
    float3 light            : LIGHT0;
    float3 eye_vec          : EYE0;
    float4 light_tex_coord  : TEXCOORD1;
    float4 light_view_pos   : LIGHT_VIEW_POS0;
};

/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;             //! ワールド行列
    float4x4 View;              //! ビュー行列
    float4x4 Projection;        //! プロジェクション行列
    float4x4 LightView;         //! ライトから見たビュー行列
    float4x4 LightProjection;   //! ライトから見たプロジェクション行列
    float4x4 ClipUV;            //! UV変換用行列
    float4   CameraPos;           //! カメラ座標
    float4   Light;               //! ライトの方向
    float4   MaterialAmbient;     //! アンビエント光
    float4   MaterialDiffuse;     //! ディヒューズ光
    float4   MaterialSpecular;    //! スペキュラー光
};

/****************************************
          テクスチャ
****************************************/

Texture2D    Texture       : register(t0); // Textureをスロット0の0番目のテクスチャレジスタに設定
SamplerState Sampler       : register(s0); // Samplerをスロット0の0番目のサンプラレジスタに設定
Texture2D    TextureDepth  : register(t1);
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
    
    return MaterialSpecular * t * MaterialSpecular.z;
    
    //// 法線ベクトル
    //float4 n = float4(nw, 0.0);
    //// ライトベクトル
    //float4 l = float4(light, 0.0);
    //// 法線とライトの内積で光の当たり具合を算出
    //float  ndl = dot(n, l);
    //// 反射ベクトルを算出
    //float4 reflect = normalize(-l + 2.0 * n * ndl);
    //
    //return MaterialSpecular * pow(saturate(dot(reflect.xyz, eye_vec)), 60) * MaterialSpecular.z;
}

/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
   // 法線ベクトル
    float4 N = float4(input.norw, 0.0);
   // ライトベクトル
    float4 L = float4(input.light, 0.0);
   // 法線とライトの内積で光の当たり具合を算出
    float NL = dot(N, L);
   // 反射ベクトルを算出
    float4 R = normalize(-L + 2.0 * N * NL);
   
    // 鏡面反射光
    //float4 specular = pow(saturate(dot(R, input.eye_vec)), 60);
    
    float4 specular = Phong(input.norw, input.eye_vec, input.light);
   
   // 拡散光
    float4 tex_color = Texture.Sample(Sampler, input.texture_pos);
    float4 diffuse = tex_color * HalfLambert(input.light, input.norw);
   
   // 環境光
    float4 ambient = diffuse / 2.0;
   
    float4 color = diffuse + specular + ambient;
    
    // 影
    //input.light_tex_coord.xyz /= input.light_tex_coord.w;
    //float max_depth_slope = max(abs(ddx(input.light_tex_coord.z)), abs(ddy(input.light_tex_coord.z)));
    //float tex_value = TextureDepth.Sample(ShadowSampler, input.light_tex_coord.xy).r;
    //float light_length = input.light_view_pos.z / input.light_view_pos.w;
    //if ((tex_value + 0.0005) > light_length)
    //{
    //    color /= 3;
    //}

    return color;
}