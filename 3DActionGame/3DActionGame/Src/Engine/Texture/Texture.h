#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <D3D11.h>
#include <string>
#include <map>
#include "../../Utility/GraphicsUtility.h"
#include "../DirectGraphics.h"

class TextureManager
{
public:
	static TextureManager* GetInstance()
	{
		static TextureManager instance;
		return &instance;
	}
	
	bool Init(ID3D11Device* device_);

	bool Load(const char* fileName_, std::string keyword_);

	void Render(std::string keyword_, DirectX::XMFLOAT3 pos_);

	TextureData* GetTexture(std::string keyword_) { return &m_Texture[keyword_]; }
	
private:
	TextureManager() :
		m_VertexShader(nullptr),
		m_PixelShader(nullptr),
		m_InputLayout(nullptr),
		m_ConstantBuffer(nullptr),
		m_SamplerState(nullptr)
	{}

	~TextureManager(){}


	bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_);
	bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_);

private:

	bool CreateShader(ID3D11Device* device_);
	bool CreateInputLayout(ID3D11Device* device_);
	bool CreateConstantBuffer(ID3D11Device* device_);
	bool CreateSamplerState(ID3D11Device* device_);

private:
	std::map<std::string, TextureData> m_Texture;
	VertexShader* m_VertexShader;
	PixelShader*  m_PixelShader;
	ID3D11InputLayout* m_InputLayout;
	ID3D11Buffer* m_ConstantBuffer;
	ConstantBuffer2D m_ConstantBufferData;
	ID3D11SamplerState* m_SamplerState;

};

#endif