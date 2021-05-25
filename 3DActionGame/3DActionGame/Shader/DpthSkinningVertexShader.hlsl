
// シェーダーに送れるボーン行列の最大数
#define MAX_BONE_MATRIX 255

// VertexShaderに送られてくるデータ構造
struct VS_IN
{
    float4 pos          : POSITION0;
    float4 nor          : NORMAL0;
    float4 color        : COLOR0;
    float2 texture_pos  : TEXCOORD0;
    uint4 bones         : BONE_INDEX;
    float4 weights      : BONE_WEIGHT;
};

// VertexShaderから出力するデータ構造
struct VS_OUT
{
    float4 pos   : SV_POSITION;
    float4 depth : POSITION0;
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

cbuffer BoneBuffer : register(b1)
{
    matrix BoneWorld[MAX_BONE_MATRIX]; // ボーンの姿勢行列
};

struct Skin
{
    float4 pos; // 頂点座標
    float3 nor; // 法線ベクトル
};


Skin SkinVert(VS_IN input)
{
    Skin output = (Skin) 0;
    
    float4 pos = input.pos;
    float3 nor = input.nor.xyz;

    // ボーン0
    uint bone = input.bones.x;
    float weight = input.weights.x;
    matrix m = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3) m);

    // ボーン1
    bone = input.bones.y;
    weight = input.weights.y;
    m = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3) m);

    // ボーン2
    bone = input.bones.z;
    weight = input.weights.z;
    m = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3) m);

    // ボーン3
    bone = input.bones.w;
    weight = input.weights.w;
    m = BoneWorld[bone];
    output.pos += weight * mul(pos, m);
    output.nor += weight * mul(nor, (float3x3) m);

    return output;
}


VS_OUT vs_main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    
    // スキンメッシュを行う
    Skin skinned = SkinVert(input);

    output.pos = mul(skinned.pos, World);
    output.pos = mul(output.pos, LightView);
    output.pos = mul(output.pos, LightProjection);
    output.depth = output.pos;

    return output;
}