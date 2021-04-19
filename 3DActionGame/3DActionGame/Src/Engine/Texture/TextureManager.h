#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <D3D11.h>
#include <string>
#include <map>
#include "../../Utility/GraphicsUtility.h"
#include "../Graphics/DirectGraphics.h"

class TextureManager
{
public:
	TextureManager() :
		m_VertexShader(nullptr),
		m_PixelShader(nullptr),
		m_InputLayout(nullptr),
		m_ConstantBuffer(nullptr),
		m_SamplerState(nullptr)
	{}

	~TextureManager()
	{
		AllRelease();
		if (m_InputLayout)m_InputLayout->Release();
		if (m_SamplerState)m_SamplerState->Release();
		if (m_ConstantBuffer)m_ConstantBuffer->Release();
	}
	
	bool Init(ID3D11Device* device_);

	bool Load(const char* fileName_, std::string keyword_);

	void Render(std::string keyword_, DirectX::XMFLOAT3 pos_);

	TextureData* GetTexture(std::string keyword_) { return &m_Texture[keyword_]; }

	/**
	* @fn void Release(std::string keyword_)
	* @brief リストから指定したオブジェクトを削除する関数
	* @param[in] object_ 削除したいオブジェクト
	* @details 確保されているメモリも一緒に解放する
	*/
	void Release(std::string keyword_);

	/**
	* @fn void AllRelease()
	* @brief 保存されているテクスチャをすべて解放する関数
	*/
	void AllRelease();
	
private:
	bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_);
	bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_);

private:

	bool CreateShader(ID3D11Device* device_);
	bool CreateInputLayout(ID3D11Device* device_);
	bool CreateConstantBuffer(ID3D11Device* device_);
	bool CreateSamplerState(ID3D11Device* device_);

private:
	std::map<std::string, TextureData> m_Texture;
	VertexShader*						m_VertexShader;
	PixelShader*						m_PixelShader;
	ID3D11InputLayout*					m_InputLayout;
	ID3D11SamplerState*					m_SamplerState;
	ID3D11Buffer*						m_ConstantBuffer;
	ConstantBuffer2D					m_ConstantBufferData;

};

#endif