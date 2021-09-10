#ifndef SPRITE_H_
#define SPRITE_H_

#include "../../Utility/GraphicsUtility.h"
#include "../../Engine/Graphics/PixelShader.h"
#include "../../Engine/Graphics/VertexShader.h"

class Sprite
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Sprite()
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~Sprite()
	{}

	void Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_);

	void Draw(DirectX::XMFLOAT3 pos_);

private:
	/**
	* @fn bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief ���_�o�b�t�@�̍쐬�֐�
	* @param[in] data_ �e�N�X�`���f�[�^
	* @param[in] device_ �O���t�B�b�N�f�o�C�X
	*/
	bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_);

	/**
	* @fn bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief �C���f�b�N�X�o�b�t�@�̍쐬�֐�
	* @param[in] data_ �e�N�X�`���f�[�^
	* @param[in] device_ �O���t�B�b�N�f�o�C�X
	*/
	bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_);
	
	/**
	* @fn bool CreateInputLayout(ID3D11Device* device_)
	* @brief ���̓��C�A�E�g�̍쐬�֐�
	* @param[in] device_ �O���t�B�b�N�f�o�C�X
	*/
	bool CreateInputLayout(ID3D11Device* device_);

	/**
	* @fn bool CreateConstantBuffer(ID3D11Device* device_)
	* @brief �萔�o�b�t�@�̍쐬�֐�
	* @param[in] device_ �O���t�B�b�N�f�o�C�X
	*/
	bool CreateConstantBuffer(ID3D11Device* device_);
private:
	TextureData   m_TextureData;
	VertexShader* m_VertexShader;
	PixelShader*  m_PixelShader;
	

	ComPtr<ID3D11Buffer>	  m_ConstantBuffer;		//! �萔�o�b�t�@�I�u�W�F�N�g
	ConstantBuffer2D		  m_ConstantBufferData;
	ComPtr<ID3D11InputLayout> m_InputLayout;			//! ���̓��C�A�E�g
};

#endif