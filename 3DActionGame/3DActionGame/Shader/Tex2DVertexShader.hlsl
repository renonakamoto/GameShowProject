

// VertexShaderに送られてくるデータ
struct VS_IN
{
    float4 pos          : POSITION0;
    float2 texture_pos  : TEXCOORD0;
};

// VertexShaderから出力するデータ
struct VS_OUT
{
    float4 pos         : SV_POSITION;
    float2 texture_pos : TEXCOORD0;
};

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix Projection;
};


// エントリーポイント
VS_OUT vs_main( VS_IN input )
{
    VS_OUT output = (VS_OUT)0;
    
    // 行列変換
    matrix wp = World * Projection;
    output.pos = mul(input.pos, wp);
    
    output.texture_pos = input.texture_pos;

	return output;
}