// シェーダーに送れるボーン行列の最大数
#define MAX_BONE_MATRIX 255

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
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;             //! ワールド行列
    float4x4 View;              //! ビュー行列
    float4x4 Projection;        //! プロジェクション行列
    float4x4 LightView;         //! ライトから見たビュー行列
    float4x4 LightProjection;   //! ライトから見たプロジェクション行列
    float4x4 ClipUV;            //! UV変換用行列
    float4 CameraPos;           //! カメラ座標
    float4 Light;               //! ライトの方向
    float4 MaterialAmbient;     //! アンビエント光
    float4 MaterialDiffuse;     //! ディヒューズ光
    float4 MaterialSpecular;    //! スペキュラー光
};

Texture2D    Texture       : register(t0); // Textureをスロット0の0番目のテクスチャレジスタに設定
Texture2D    TextureDepth  : register(t1);
SamplerState Sampler       : register(s0); // Samplerをスロット0の0番目のサンプラレジスタに設定
SamplerState ShadowSampler : register(s1);

float4 ps_main(PS_IN input) : SV_Target
{
    // 法線ベクトル
    float4 N = float4(input.norw, 0.0);
    // ライトベクトル
    float4 L = float4(input.light, 0.0);
    // 法線とライトの内積で光の当たり具合を算出
    float NL = saturate(dot(N, L));
    // 反射ベクトルを算出
    float4 R = normalize(-L + 2.0 * N * NL);

    // 鏡面反射光
    float4 specular = pow(saturate(dot(R, input.eye_vec)), 60);

    // 拡散光
    float4 tex_color = Texture.Sample(Sampler, input.texture_pos);
    float4 diffuse   = (tex_color * tex_color.w) + (MaterialDiffuse * MaterialDiffuse.w);  
    
    // 環境光
    float4 ambient = diffuse / 2.0;

    // フォンシェーディング(アンビエント光 + ディヒューズ光 + スペキュラー光)
    float4 color = ambient + (diffuse * NL) + specular;

    
    // 影
    input.light_tex_coord.xyz /= input.light_tex_coord.w;
    float max_depth_slope = max(abs(ddx(input.light_tex_coord.z)), abs(ddy(input.light_tex_coord.z)));
    float tex_value = TextureDepth.Sample(ShadowSampler, input.light_tex_coord.xy).r;
    float light_length = input.light_view_pos.z / input.light_view_pos.w;
    if ((tex_value + 0.0005) > light_length)
    {
        color /= 3;
    }

    return color;
}