// VertexShaderに送られてくるデータ構造
struct VS_IN
{
        float4 pos : POSITION0;
        float4 nor : NORMAL0;
        float4 texture_pos : TEXTURE0;
};
 
// VertexShaderから出力するデータ構造
struct VS_OUT
{
        float4 pos : SV_POSITION;
        float4 nor : NORMAL;
        float4 texture_pos : TEXTURE0;
};
 
cbuffer ConstantBuffer
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4   CameraPos;
    float4   LightVector;
    float4   LightColor;
    float4   MaterialAmbient;
    float4   MaterialDiffuse;
    float4   MaterialSpecular;
};
 
VS_OUT vs_main( VS_IN input )
{
        VS_OUT output;

        // ローカル座標 * ワールド座標変換行列
        output.pos = mul(input.pos,  World);
        // ワールド座標 * ビュー座標変換行列
        output.pos = mul(output.pos, View);
        // ビュー座標 * プロジェクション座標変換行列
        output.pos = mul(output.pos, Projection);

        float4 normal;
        
        input.nor.w = 0.0;

        normal = mul(input.nor, World).xyzw;
        normal = normalize(normal);

        output.nor = saturate(dot(normal, LightVector));

        return output;
}