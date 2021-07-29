
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

float Lambert(float3 lig_dir, float3 normal)
{
    return saturate(dot(normal, lig_dir));
}

float Phong(float3 normal, float3 eye_vec, float3 lig_dir)
{
    // ライトの反射ベクトルを求める
    float  ndl = saturate(dot(normal, lig_dir));
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
   // ディフューズカラー
   float4 diffuse_color = Texture.Sample(Sampler, input.texture_pos);
   
   // 法線とライトのベクトルの内積を計算し0～1に補正する -> 反射率
   float ndl = saturate(dot(input.norw, Light.xyz));
   // 0.0～1.0に1/2を乗算し1/2を加算することで0.5～1.0に値を補正する
   float half_ndl = ndl * 0.5 + 0.5;
   // 二乗することで、0.5～1.0の滑らかなカーブになる
   float square_ndl = half_ndl * half_ndl;
   
   // ディフューズカラーと乗算し反射した色を算出
   diffuse_color *= square_ndl;
    
   // スペキュラーカラー
   float4 specular_color = Phong(input.norw, input.eye_vec, input.light);
    
   // 環境光
   float4 ambient_color = diffuse_color / 2.0;
   
   float4 final_color = diffuse_color + specular_color + ambient_color;
    
    // 出力
    return final_color;
}