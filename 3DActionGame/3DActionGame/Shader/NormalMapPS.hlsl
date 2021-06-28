
/****************************************
           入力パラメータ
****************************************/

// PixelShaderに送られてくるデータ構造
struct PS_IN
{
    float4 pos                     : SV_POSITION;
    float4 posw                    : POSITION0;
    float3 norw                    : NORMAL0;
    float2 texture_pos             : TEXCOORD0;
    float3 light                   : LIGHT0;
    float3 eye_vec                 : EYE0;
    float4 light_tex_coord         : TEXCOORD1;
    float4 light_view_pos          : LIGHT_VIEW_POS0;
    float4 light_tangent_direct    : TANGENT_LIGHT;
};

/****************************************
          定数バッファ
****************************************/
 
cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //! ワールド行列
    float4x4 View; //! ビュー行列
    float4x4 Projection; //! プロジェクション行列
    float4x4 LightView; //! ライトから見たビュー行列
    float4x4 LightProjection; //! ライトから見たプロジェクション行列
    float4x4 ClipUV; //! UV変換用行列
    float4 CameraPos; //! カメラ座標
    float4 Light; //! ライトの方向
    float4 MaterialAmbient; //! アンビエント光
    float4 MaterialDiffuse; //! ディヒューズ光
    float4 MaterialSpecular; //! スペキュラー光
};

/****************************************
          テクスチャ
****************************************/

Texture2D Texture : register(t0);           // Textureをスロット0の0番目のテクスチャレジスタに設定
SamplerState Sampler : register(s0);        // Samplerをスロット0の0番目のサンプラレジスタに設定
Texture2D TextureDepth : register(t1);
SamplerState ShadowSampler : register(s1);
Texture2D NormalTexture : register(t2);


/****************************************
          共通関数
****************************************/

float4 HalfLambert(float ndl)
{
    float half_ndl = ndl * 0.5 + 0.5;
    float square_ndl = half_ndl * half_ndl;
	
    return MaterialDiffuse * square_ndl * MaterialDiffuse.w;
}

float4 Phong(float3 nw, float3 eye_vec, float3 light)
{
    // 法線ベクトル
    float4 n = float4(nw, 0.0);
    // ライトベクトル
    float4 l = float4(light, 0.0);
    // 法線とライトの内積で光の当たり具合を算出
    float ndl = dot(n, l);
    // 反射ベクトルを算出
    float4 reflect = normalize(-l + 2.0 * n * ndl);
    
    return MaterialSpecular * pow(saturate(dot(reflect.xyz, eye_vec)), 60) * MaterialSpecular.z;
}


/****************************************
          インターフェース
****************************************/

/*
    ライティングのインターフェース
*/
interface BaseLight
{
    float4 GetColor(PS_IN input);
};

/****************************************
          クラス
****************************************/

class SimpleShading : BaseLight
{
    float4 GetColor(PS_IN input)
    {
        /* AmbientColor */
        float4 ambient = MaterialAmbient * MaterialAmbient.w;
        
        /* DiffuseColor */
        float4 tex_color = Texture.Sample(Sampler, input.texture_pos);
        float ndl = saturate(dot(input.norw, input.light));
        float4 diffuse = HalfLambert(saturate(ndl)) + tex_color;
        
        /* SpecularColor */
        float4 specular = Phong(input.norw, input.eye_vec, input.light);
        
        return ambient + diffuse + specular;
    }
};

class PhongShading : BaseLight
{
    float4 GetColor(PS_IN input)
    {
        float ndl = saturate(dot(input.norw, input.light));
        float4 diffuse = HalfLambert(ndl);
        
        float4 specular = Phong(input.norw, input.eye_vec, input.light);
        
        return diffuse + specular;

    }
};

/****************************************
            エントリー関数
****************************************/
float4 ps_main(PS_IN input) : SV_Target
{
   // 法線ベクトル
    float4 N = float4(input.norw, 0.0);
   // ライトベクトル
    float4 L = float4(input.light, 0.0);
   // 法線とライトの内積で光の当たり具合を算出
    float NL = dot(N, L);
   // 反射ベクトルを算出
    float4 R = normalize(-L + 2.0 * N * NL);
   
    // 鏡面反射光
    float4 specular = pow(saturate(dot(R, input.eye_vec)), 50);
    
    //float4 specular = Phong(input.norw, input.eye_vec, input.light);
   
    float3 normal_color = NormalTexture.Sample(Sampler, input.texture_pos);
    float3 normal_vec = 2 * normal_color - 1.0f;
    normal_vec = normalize(normal_vec);
   
    float3 bright = dot(input.light_tangent_direct.xyz, normal_vec);
    bright = max(0.0, bright);
   
   // 拡散光
    float4 tex_color = Texture.Sample(Sampler, input.texture_pos);
    float4 diffuse = HalfLambert(saturate(NL)) + tex_color;
   
   // 環境光
    float4 ambient = diffuse / 2.0;
    
    float3 normal_in_view = mul(input.norw, (float3x3) View);
    float  power1 = 1.0 - max(0.0, dot((float3)-Light, input.norw));
    float  power2 = 1.0 - max(0.0, normal_in_view.z * -1.0);
    float  lim_power = power1 * power2;
    lim_power = pow(lim_power, 4.0);
   
    float4 color = ambient + diffuse + specular + lim_power;
    
    // 影
    //input.light_tex_coord.xyz /= input.light_tex_coord.w;
    //float max_depth_slope = max(abs(ddx(input.light_tex_coord.z)), abs(ddy(input.light_tex_coord.z)));
    //float tex_value = TextureDepth.Sample(ShadowSampler, input.light_tex_coord.xy).r;
    //float light_length = input.light_view_pos.z / input.light_view_pos.w;
    //if ((tex_value + 0.0005) > light_length)
    //{
    //    color /= 3;
    //}

    
    return color + float4(0.1, 0.1, 0.1, 0.0);
    //return color;
}