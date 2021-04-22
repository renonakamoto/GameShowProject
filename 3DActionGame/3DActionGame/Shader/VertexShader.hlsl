
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
        float4 pos             : SV_POSITION;   
        float4 posw            : POSITION0;
        float3 norw            : NORMAL0;
        float2 texture_pos     : TEXCOORD0;
        float3 light           : TEXCOORD1;
        float3 eye_vec         : TEXCOORD2;
        float4 light_tex_coord : TEXCOORD3;
        float4 light_view_pos  : TEXCOORD4;
};
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;             //! ワールド行列
    float4x4 View;              //! ビュー行列
    float4x4 Projection;        //! プロジェクション行列
    float4x4 LightView;         //! ライトのビュー行列
    float4x4 ClipUV;            //! UV変換用行列
    float4   CameraPos;         //! カメラ座標
    float4   Light;             //! ライトの方向
    float4   MaterialAmbient;   //! アンビエント光
    float4   MaterialDiffuse;   //! ディヒューズ光
    float4   MaterialSpecular;  //! スペキュラー光
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

        // スキンメッシュを行う
        Skin skinned = SkinVert(input);
        
        // ワールド座標に変換
        output.posw = mul(skinned.pos, World);
        // ワールド座標 * ビュー座標変換行列
        output.pos = mul(output.posw, View);
        // ビュー座標 * プロジェクション座標変換行列
        output.pos = mul(output.pos, Projection);

        // テクスチャ座標
        output.texture_pos = input.texture_pos;
        
        // 法線ベクトル
        output.norw = normalize(mul(skinned.nor, (float3x3)World));
        //output.norw = saturate(dot(normal, Light));
        
        // カメラの向き
        output.eye_vec = normalize(CameraPos - output.posw);

        // ライトの方向
        output.light = normalize(Light);

        /*
            シャドウマップ用
        */
        
        // ライト視点でのビュー座標変換
        output.light_view_pos = mul(output.posw, LightView);
        // ライト視点でのプロジェクション座標変換
        output.light_view_pos = mul(output.light_view_pos, Projection);
        // テクスチャUVの変換
        output.light_tex_coord = mul(output.light_view_pos, ClipUV);

        return output;
}