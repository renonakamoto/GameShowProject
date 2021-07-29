
/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos                     : SV_POSITION;
    float4 posw                    : POSITION0;
    float3 norw                    : NORMAL0;
    float2 texture_pos             : TEXCOORD0;
    float3 light                   : LIGHT0;
    float3 eye_vec                 : EYE0;
    float4 light_tex_coord         : TEXCOORD1;
    float4 light_view_pos          : LIGHT_VIEW_POS0;
    float4 light_tangent_direct    : TANGENT_LIGHT;
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

Texture2D Texture : register(t0);           // Textureをスロット0の0番目のテクスチャレジスタに設定
SamplerState Sampler : register(s0);        // Samplerをスロット0の0番目のサンプラレジスタに設定
Texture2D TextureDepth : register(t1);
SamplerState ShadowSampler : register(s1);
Texture2D NormalTexture : register(t2);


/****************************************
          共通関数
****************************************/

float4 HalfLambert(float ndl)
{
    float half_ndl = ndl * 0.5 + 0.5;
    float square_ndl = half_ndl * half_ndl;
	
    return MaterialDiffuse * square_ndl * MaterialDiffuse.w;
}

float Phong(float3 normal, float3 eye_vec, float3 lig_dir)
{
    // ライトの反射ベクトルを求める
    float ndl = saturate(dot(normal, lig_dir));
    float3 ref_vec = normalize(-lig_dir + 2.0 * normal * ndl);
    
    // 鏡面反射の強さを算出
    float r_d_e = saturate(dot(ref_vec, eye_vec));
    
    // 強さを絞る
    r_d_e = pow(r_d_e, 60.0);
    
    return r_d_e;
}
/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
    // 鏡面反射光
    float4 specular = Phong(input.norw, input.eye_vec, input.light);
   
   // 拡散光
    float n_d_l = saturate(dot(input.norw, input.light));
    float4 tex_color = Texture.Sample(Sampler, input.texture_pos);
    float4 diffuse = HalfLambert(n_d_l) + tex_color;
   
   // 環境光
    float4 ambient = diffuse / 2.0;
    
    // リムライト
    float3 normal_in_view = mul(input.norw, (float3x3) View);
    float  power1         = 1.0 - max(0.0, dot((float3)-Light, input.norw));
    float  power2         = 1.0 - max(0.0, normal_in_view.z * -1.0);
    float  lim_power = power1 * power2;
    lim_power = pow(lim_power, 4.0);
   
    float4 color = ambient + diffuse + specular + lim_power;
    
    // 出力
    return color + float4(0.1, 0.1, 0.1, 0.0);
}