#ifndef GRAPHICS_UTILITY_H_
#define GRAPHICS_UTILITY_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

struct ConstantBuffer
{
    DirectX::XMFLOAT4X4 World;
    DirectX::XMFLOAT4X4 View;
    DirectX::XMFLOAT4X4 Projection;
    DirectX::XMFLOAT4X4 LightView;
    DirectX::XMFLOAT4X4 ClipUV;
    DirectX::XMMATRIX   Bone[255];
    DirectX::XMFLOAT4   CameraPos;
    DirectX::XMFLOAT4   Light;
    DirectX::XMFLOAT4   Attenuation;
    DirectX::XMFLOAT4   MaterialAmbient;
    DirectX::XMFLOAT4   MaterialDiffuse;
    DirectX::XMFLOAT4   MaterialSpecular;

    ConstantBuffer()
    {
        ZeroMemory(this, sizeof(ConstantBuffer));
    }
};

struct ConstLightBuffer
{
    // 光源座標
    DirectX::XMFLOAT4   LightPos;
    // 光源減衰パラメータ
    DirectX::XMFLOAT4   Attenuation;

    ConstLightBuffer()
    {
        ZeroMemory(this, sizeof(ConstLightBuffer));
    }
};

struct ConstantBuffer2D
{
    DirectX::XMMATRIX m_WP;

    ConstantBuffer2D()
    {
        ZeroMemory(this, sizeof(ConstantBuffer2D));
    }
};


struct CustomVertex {
    float pos[3];
    float col[4];

    CustomVertex()
    {
        ZeroMemory(this, sizeof(CustomVertex));
    }
};


struct Vertex2D {
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT2 TexturePos;
};

struct CVertex {
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT4 Color;
    DirectX::XMFLOAT2 TexturePos;

    UINT  Index[4];
    float Weight[4];

    CVertex()
    {
        ZeroMemory(this, sizeof(CVertex));
    }
};

struct ObjMaterial
{
    float Ambient[4];
    float Diffuse[4];
    float Specular[4];

    ObjMaterial() :
        Ambient { 0,0,0,1 },
        Diffuse { 0,0,0,1 },
        Specular{ 0,0,0,1 }
    {
    }
};

#endif