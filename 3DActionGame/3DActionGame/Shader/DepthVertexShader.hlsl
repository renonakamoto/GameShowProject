// VertexShaderに送られてくるデータ構造
struct VS_IN
{
    float4 pos          : POSITION0;
    float4 nor          : NORMAL0;
    float2 texture_pos  : TEXCOORD0;
};

// VertexShaderから出力するデータ構造
struct VS_OUT
{
    float4 pos   : SV_POSITION;
    float4 depth : POSITION0;
};

cbuffer ConstantBuffer
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 LightView;
    float4x4 ClipUV;
    float4   CameraPos;
    float4   Light;
    float4   MaterialAmbient;
    float4   MaterialDiffuse;
    float4   MaterialSpecular;
};

VS_OUT vs_main( VS_IN input )
{
    VS_OUT output = (VS_OUT)0;

    output.pos = mul(input.pos, World);
    output.pos = mul(output.pos, LightView);
    output.pos = mul(output.pos, Projection);
    output.depth = output.pos;

	return output;
}