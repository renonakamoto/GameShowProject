
// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos         : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

// テクスチャ情報
Texture2D    Texture : register(t0);
SamplerState Sampler : register(s0);


// エントリーポイント
float4 ps_main(PS_IN input) : SV_TARGET
{
    // そのまま出力
    return Texture.Sample(Sampler, input.texture_pos);
}