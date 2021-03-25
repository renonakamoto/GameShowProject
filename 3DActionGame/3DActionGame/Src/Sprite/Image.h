#ifndef IMAGE_H_
#define IMAGE_H_

#include <D3D11.h>
#include <DirectXMath.h>
#include <string>

class Image
{
public:
	Image(std::string textureKeyword_):
		m_Texture(nullptr)
	{}

	~Image()
	{}
	
	void Draw(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, float pivot_x = 0.0f, float pivot_y = 0.0f);

private:
	

private:
	ID3D11ShaderResourceView* m_Texture;	// テクスチャ

};

#endif