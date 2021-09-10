#ifndef SPRITE_H_
#define SPRITE_H_

#include "../../Utility/GraphicsUtility.h"
#include "../../Engine/Graphics/PixelShader.h"
#include "../../Engine/Graphics/VertexShader.h"

class Sprite
{
public:
	/**
	* @brief コンストラクタ
	*/
	Sprite()
	{}

	/**
	* @brief デストラクタ
	*/
	~Sprite()
	{}

	void Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_);

	void Draw(DirectX::XMFLOAT3 pos_);

private:
	/**
	* @fn bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief 頂点バッファの作成関数
	* @param[in] data_ テクスチャデータ
	* @param[in] device_ グラフィックデバイス
	*/
	bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_);

	/**
	* @fn bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief インデックスバッファの作成関数
	* @param[in] data_ テクスチャデータ
	* @param[in] device_ グラフィックデバイス
	*/
	bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_);
	
	/**
	* @fn bool CreateInputLayout(ID3D11Device* device_)
	* @brief 入力レイアウトの作成関数
	* @param[in] device_ グラフィックデバイス
	*/
	bool CreateInputLayout(ID3D11Device* device_);

	/**
	* @fn bool CreateConstantBuffer(ID3D11Device* device_)
	* @brief 定数バッファの作成関数
	* @param[in] device_ グラフィックデバイス
	*/
	bool CreateConstantBuffer(ID3D11Device* device_);
private:
	TextureData   m_TextureData;
	VertexShader* m_VertexShader;
	PixelShader*  m_PixelShader;
	

	ComPtr<ID3D11Buffer>	  m_ConstantBuffer;		//! 定数バッファオブジェクト
	ConstantBuffer2D		  m_ConstantBufferData;
	ComPtr<ID3D11InputLayout> m_InputLayout;			//! 入力レイアウト
};

#endif