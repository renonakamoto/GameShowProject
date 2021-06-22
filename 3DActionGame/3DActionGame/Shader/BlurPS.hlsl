
// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

// テクスチャ情報
Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);

Texture2D BlurTexture : register(t1);

// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{
    float4 base_color = Texture.Sample(Sampler, input.texture_pos);
    float4 blur_color = Texture.Sample(Sampler, input.texture_pos);
    
    float offset_u = 1.5 / 1280.0;
    float offset_v = 1.5 / 720.0;
    
    //offset_u = 0.0;
    //offset_v = 0.0;
    
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2( offset_u,       0.0));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2(-offset_u,       0.0));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2(      0.0,  offset_v));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2(      0.0, -offset_v));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2( offset_u,  offset_v));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2( offset_u, -offset_v));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2(-offset_u,  offset_v));
    blur_color += Texture.Sample(Sampler, input.texture_pos + float2(-offset_u, -offset_v));
    
    blur_color /= 9.0;
    
    float t = BlurTexture.Sample(Sampler, input.texture_pos).r;
    
    float4 color = lerp(base_color, blur_color, t);
    
    return color;
}