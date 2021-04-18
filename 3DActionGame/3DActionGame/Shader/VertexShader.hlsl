
#define ENABLE_SKINMESH

// シェーダーに送れるボーン行列の最大数
#define MAX_BONE_MATRIX 255

// VertexShaderに送られてくるデータ構造
struct VS_IN
{
        float4 pos          : POSITION0;
        float4 nor          : NORMAL0;
        float4 color        : COLOR0;
        float2 texture_pos  : TEXCOORD0;
        uint4  bones        : BONE_INDEX;
        float4 weights      : BONE_WEIGHT;
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
 
cbuffer ConstantBuffer : register(b0)
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

cbuffer BoneBuffer : register(b1)
{
    matrix   BoneWorld[MAX_BONE_MATRIX];
};

struct Skin
{
    float4 pos;
    float3 nor;
};


Skin SkinVert(VS_IN input)
{
    Skin output = (Skin)0;
    
    float4 pos = input.pos;
    float3 nor = input.nor.xyz;

    // ボーン0
    uint bone    = input.bones.x;
    float weight = input.weights.x;
    matrix m     = BoneWorld[bone];
    output.pos  += weight * mul(pos, m);
    output.nor  += weight * mul(nor, (float3x3)m);

    // ボーン1
    bone        = input.bones.y;
    weight      = input.weights.y;
    m           = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3)m);

    // ボーン2
    bone        = input.bones.z;
    weight      = input.weights.z;
    m           = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3)m);

    // ボーン3
    bone        = input.bones.w;
    weight      = input.weights.w;
    m           = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3)m);

    return output;
}

 
VS_OUT vs_main( VS_IN input )
{
        VS_OUT output = (VS_OUT)0;

#ifdef ENABLE_SKINMESH
        Skin skinned = SkinVert(input);
        output.posw = mul(skinned.pos, World);
#else
        output.posw = mul(input.pos, World);
#endif
        // ワールド座標 * ビュー座標変換行列
        output.pos = mul(output.posw, View);
        // ビュー座標 * プロジェクション座標変換行列
        output.pos = mul(output.pos, Projection);

        // テクスチャ座標
        output.texture_pos = input.texture_pos;
        
#ifdef ENABLE_SKINMESH
        // 法線ベクトル
        output.norw = mul(skinned.nor, (float3x3)World);
#else
        // 法線ベクトル
        output.norw = mul(input.nor, (float3x3)World);
#endif
        
        output.eye_vec = normalize(CameraPos - output.posw);
        output.light = normalize(Light);
        
        output.light_view_pos = mul(output.posw, LightView);
        output.light_view_pos = mul(output.light_view_pos, Projection);
        //output.light_tex_coord = output.light_view_pos;//mul(output.light_view_pos, ClipUV);
        output.light_tex_coord = mul(output.light_view_pos, ClipUV);

        return output;
}