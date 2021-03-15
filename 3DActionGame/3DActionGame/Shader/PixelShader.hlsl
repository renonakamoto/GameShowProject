// シェーダーに送れるボーン行列の最大数
#define MAX_BONE_MATRIX 255

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 posw : POSITION0;
    float3 norw : NORMAL0;
    float2 texture_pos : TEXCOORD0;
    float3 light : TEXCOORD1;
    float3 eye_vec : TEXCOORD2;
    float4 light_tex_coord : TEXCOORD3;
    float4 light_view_pos : TEXCOORD4;
};
 
cbuffer ConstantBuffer
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 LightView;
    float4x4 ClipUV;
    matrix   BoneWorld[MAX_BONE_MATRIX];
    float4   CameraPos;
    float4   Light;
    float4   Attenuation;
    float4   MaterialAmbient;
    float4   MaterialDiffuse;
    float4   MaterialSpecular;
};

Texture2D    Texture : register(t0[0]); // Textureをスロット0の0番目のテクスチャレジスタに設定
Texture2D    TextureDepth : register(t1[0]);
SamplerState Sampler : register(s0[0]); // Samplerをスロット0の0番目のサンプラレジスタに設定
SamplerState ShadowSampler : register(s1[0]);

float4 ps_main(PS_IN input) : SV_Target
{
    // 環境光
    float4 ambient = MaterialAmbient;
    // 拡散光
    float NL = saturate(dot(input.norw, input.light));
    float4 diffuse = Texture.Sample(Sampler, input.texture_pos);
    //float4 diffuse = (MaterialDiffuse / 2 + Texture.Sample(Sampler, input.texture_pos) / 2) * NL;
    // 鏡面反射光
    float3 reflect = normalize(2 * NL * input.norw - input.light);
    float4 specular = pow(saturate(dot(reflect, input.eye_vec)), 4) * MaterialSpecular;
    // フォン
    float4 color = diffuse;
    // アルファブレンド
    //color.a = MaterialDiffuse.a;

    // 影
    //input.light_tex_coord /= input.light_tex_coord.w;
    //float max_depth_slope = max(abs(ddx(input.light_tex_coord.z)), abs(ddy(input.light_tex_coord.z)));
    //float tex_value = TextureDepth.Sample(Sampler, input.light_tex_coord).r;
    //float light_length = input.light_view_pos.z / input.light_view_pos.w;
    //if ((tex_value) < light_length)
    //{
    //    color /= 3;
    //}

    return color;
}