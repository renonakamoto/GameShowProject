
// シェーダーに送れるボーン行列の最大数
#define MAX_BONE_MATRIX 255

/****************************************
           入力パラメータ
****************************************/

// VertexShaderに送られてくるデータ構造
struct VS_IN
{
    float4 pos          : POSITION0;
    float4 nor          : NORMAL0;
    float4 color        : COLOR0;
    float2 texture_pos  : TEXCOORD0;
    uint4  bones        : BONE_INDEX;
    float4 weights      : BONE_WEIGHT;
    float4 tangent      : TANGENT0;
    float4 binormal     : BINORMAL0;
};
 
/****************************************
           出力パラメータ
****************************************/

// VertexShaderから出力するデータ構造
struct VS_OUT
{
        float4 pos                  : SV_POSITION;   
        float4 posw                 : POSITION0;
        float3 norw                 : NORMAL0;
        float2 texture_pos          : TEXCOORD0;
        float3 light                : LIGHT0;
        float3 eye_vec              : EYE0;
        float4 light_tex_coord      : TEXCOORD1;
        float4 light_view_pos       : LIGHT_VIEW_POS0;
        float4 light_tangent_direct : TANGENT_LIGHT;
};


/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;             //! ワールド行列
    float4x4 View;              //! ビュー行列
    float4x4 Projection;        //! プロジェクション行列
    float4x4 LightView;         //! ライトから見たビュー行列
    float4x4 LightProjection;   //! ライトから見たプロジェクション行列
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

// スキンメッシュ後の頂点情報
struct Skin
{
    float4 pos;      // 頂点座標
    float3 nor;      // 法線ベクトル
    float3 tangent;  // 接ベクトル
    float3 binormal; // 従法線ベクトル
};

/****************************************
          共通関数
****************************************/

Skin SkinVert(VS_IN input)
{
    Skin output = (Skin)0;
    
    float4 pos   = input.pos;
    float3 nor   = input.nor.xyz;
    float3 tan   = input.tangent.xyz;
    float3 binor = input.binormal.xyz;

    // ボーン0
    uint   bone      = input.bones.x;
    float  weight    = input.weights.x;
    matrix m         = BoneWorld[bone];
    output.pos      += weight * mul(pos, m);
    output.nor      += weight * mul(nor, (float3x3) m);
    output.tangent  += weight * mul(tan, (float3x3) m);
    output.binormal += weight * mul(binor, (float3x3) m);

    // ボーン1
    bone             = input.bones.y;
    weight           = input.weights.y;
    m                = BoneWorld[bone];
    output.pos      += weight * mul(pos, m);
    output.nor      += weight * mul(nor, (float3x3)m);
    output.tangent  += weight * mul(tan, (float3x3) m);
    output.binormal += weight * mul(binor, (float3x3) m);
    
    // ボーン2
    bone             = input.bones.z;
    weight           = input.weights.z;
    m                = BoneWorld[bone];
    output.pos      += weight * mul(pos, m);
    output.nor      += weight * mul(nor, (float3x3)m);
    output.tangent  += weight * mul(tan, (float3x3) m);
    output.binormal += weight * mul(binor, (float3x3) m);

    // ボーン3
    bone             = input.bones.w;
    weight           = input.weights.w;
    m                = BoneWorld[bone];
    output.pos      += weight * mul(pos, m);
    output.nor      += weight * mul(nor, (float3x3)m);
    output.tangent  += weight * mul(tan, (float3x3) m);
    output.binormal += weight * mul(binor, (float3x3) m);

    return output;
}

float4x4 InvTangentMatrix(float3 tangent_, float3 binormal_, float3 normal_)
{
    float4x4 mat =
    {
        float4(tangent_, 0.0),
        float4(binormal_, 0.0),
        float4(normal_, 0.0),
        float4(0.0, 0.0, 0.0, 1.0),
    };
	
    return transpose(mat);
}

 
/****************************************
            エントリー関数
****************************************/

VS_OUT vs_main( VS_IN input )
{
    VS_OUT output = (VS_OUT)0;

    // スキンメッシュを行う
    Skin skinned = SkinVert(input);
    
    // ワールド座標変換
    output.posw = mul(skinned.pos, World);
    // ビュー座標変換
    output.pos = mul(output.posw, View);
    // プロジェクション座標変換
    output.pos = mul(output.pos, Projection);

    // テクスチャ座標
    output.texture_pos = input.texture_pos;
    
    // 法線ベクトル
    output.norw = normalize(mul(skinned.nor, (float3x3)World));
    
    // カメラの向き
    output.eye_vec = normalize(CameraPos - output.posw);

    // ライトの方向
    output.light = normalize(Light);
    
    output.light_tangent_direct = mul(Light, InvTangentMatrix(skinned.tangent.xyz, skinned.binormal.xyz, skinned.nor.xyz));


    /* シャドウマップ処理 */    
    
    // ライト視点でのビュー座標変換
    output.light_view_pos = mul(output.posw, LightView);
    // ライト視点でのプロジェクション座標変換
    output.light_view_pos = mul(output.light_view_pos, LightProjection);
    // テクスチャUVの変換
    output.light_tex_coord = mul(output.light_view_pos, ClipUV);

    return output;
}