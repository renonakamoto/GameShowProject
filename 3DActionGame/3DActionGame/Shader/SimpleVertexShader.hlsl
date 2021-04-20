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
    float4   CameraPos;
    float4   Light;
    float4   MaterialAmbient;
    float4   MaterialDiffuse;
    float4   MaterialSpecular;
};
 
VS_OUT vs_main( VS_IN input )
{
        VS_OUT output = (VS_OUT)0;
        
        // ローカル座標 * ワールド座標変換行列
        output.posw = mul(input.pos,  World);
        // ワールド座標 * ビュー座標変換行列
        output.pos = mul(output.posw, View);
        // ビュー座標 * プロジェクション座標変換行列
        output.pos = mul(output.pos, Projection);

        // テクスチャ座標
        output.texture_pos = input.texture_pos;

        // 法線ベクトル
        output.norw = normalize ( mul(input.nor, (float3x3)World) );

        output.texture_pos = input.texture_pos;

        output.eye_vec = normalize(CameraPos - output.posw);
        
        output.light = normalize(Light);
        
        output.light_view_pos = mul(output.posw, LightView);
        output.light_view_pos = mul(output.light_view_pos, Projection);
        output.light_tex_coord = mul(output.light_view_pos, ClipUV);

        return output;
}