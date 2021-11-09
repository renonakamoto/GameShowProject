#include "Sprite.h"
#include "../../Engine/Engine.h"

void Sprite::Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_)
{
	m_TextureData.Texture = tex_;
	m_TextureData.Width   = width_;
	m_TextureData.Height  = height_;
	m_VertexShader = vs_;
	m_PixelShader = ps_;
	
	CreateVertexBuffer(m_TextureData, GRAPHICS->GetDevice());
	CreateIndexBuffer(m_TextureData, GRAPHICS->GetDevice());

	CreateInputLayout(GRAPHICS->GetDevice());
	CreateConstantBuffer(GRAPHICS->GetDevice());
}

void Sprite::Draw(DirectX::XMFLOAT3 pos_)
{
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ���̓��C�A�E�g��ݒ�
	context->IASetInputLayout(m_InputLayout.Get());

	// ���_�o�b�t�@�̓o�^
	UINT stride = sizeof(Vertex2D);
	UINT offset = 0;
	context->IASetVertexBuffers(0U, 1U, m_TextureData.VertexBuffer.GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�̓o�^
	context->IASetIndexBuffer(m_TextureData.IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0U);

	// �v���~�e�B�u�^�C�v�̐ݒ�
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ���[���h�s��̐ݒ�
	int client_width  = WINDOW->GetClientWidth();
	int client_height = WINDOW->GetClientHeight();
	m_ConstantBufferData.World = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(1.f - (pos_.x / (client_width / 2)), 1.f - (pos_.y / (client_height / 2)), pos_.z));

	// ���ˉe�s��̐ݒ�
	m_ConstantBufferData.Projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, client_width, client_height, 0.0f, -1.0f, 1.0f));
	context->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_ConstantBufferData, 0U, 0U);

	// �萔�o�b�t�@�̐ݒ�
	context->VSSetConstantBuffers(0U, 1U, m_ConstantBuffer.GetAddressOf());

	// �V�F�[�_�[�̐ݒ�
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0U);

	// �e�N�X�`�����V�F�[�_�ɓo�^
	ID3D11SamplerState* sampler = GRAPHICS->GetSSamplerState();
	context->PSSetSamplers(0U, 1U, &sampler);
	context->PSSetShaderResources(0U, 1U, m_TextureData.Texture.GetAddressOf());

	context->PSSetShaderResources(1U, 1U, TEX_MANAGER->GetTexture("BlurMap")->Texture.GetAddressOf());

	// �C���f�b�N�X�o�b�t�@�ŕ`��
	context->DrawIndexed(6U, 0U, 0U);
}

bool Sprite::CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	float tex_width = static_cast<float>(data_.Width);
	float tex_height = static_cast<float>(data_.Height);

	// �l�p�`�|���S���̒��_���`
	Vertex2D vertices[4]{
		{{0.0f,		 0.0f,		 0.0f}, {0.0f, 0.0f}},	// ���㒸�_
		{{tex_width, 0.0f,		 0.0f}, {1.0f, 0.0f}},	// �E�㒸�_
		{{0.0f,		 tex_height, 0.0f}, {0.0f, 1.0f}},	// �������_
		{{tex_width, tex_height, 0.0f}, {1.0f, 1.0f}}	// �E�����_
	};

	// �o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = sizeof(Vertex2D) * 4;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;

	// ���\�[�X�̐ݒ�
	D3D11_SUBRESOURCE_DATA init_data;
	ZeroMemory(&init_data, sizeof(init_data));
	init_data.pSysMem = vertices;

	// ���_�o�b�t�@�̍쐬
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,										// �o�b�t�@���
		&init_data,										    // ���\�[�X���
		data_.VertexBuffer.GetAddressOf())))								// �쐬���ꂽ�o�b�t�@�̊i�[��
	{
		return false;
	}

	return true;
}

bool Sprite::CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	WORD index[]{
		0, 1, 2,
		2, 1, 3
	};

	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth	   = sizeof(DWORD) * 6;	// �o�b�t�@�̃T�C�Y
	buffer_desc.Usage		   = D3D11_USAGE_DEFAULT;				// �g�p���@
	buffer_desc.BindFlags	   = D3D11_BIND_INDEX_BUFFER;			// BIND�ݒ�
	buffer_desc.CPUAccessFlags = 0;								// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = index;	// �o�b�t�@�̒��g�̐ݒ�

	// �o�b�t�@�쐬
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,			// �o�b�t�@���
		&init_data,			// ���\�[�X���
		data_.IndexBuffer.GetAddressOf())))	// �쐬���ꂽ�o�b�t�@�̊i�[��
	{
		return false;
	}

	return true;
}

bool Sprite::CreateInputLayout(ID3D11Device* device_)
{
	D3D11_INPUT_ELEMENT_DESC vertex_desc[]{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,							  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,        0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//���_���C�A�E�g�쐬
	if (FAILED(device_->CreateInputLayout(
		vertex_desc,				// ���C�A�E�g�ݒ�
		ARRAYSIZE(vertex_desc),		// �z��T�C�Y
		m_VertexShader->GetData(),	// ���C�A�E�g�Ɗ֘A�t���钸�_�V�F�[�_�̃f�[�^
		m_VertexShader->GetSize(),	// ���C�A�E�g�Ɗ֘A�t���钸�_�V�F�[�_�̃T�C�Y
		m_InputLayout.GetAddressOf())))			// �쐬���ꂽ���_���C�A�E�g�̊i�[��
	{
		return false;
	}

	return true;
}

bool Sprite::CreateConstantBuffer(ID3D11Device* device_)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(ConstantBuffer2D);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	if (FAILED(device_->CreateBuffer(&buffer_desc, nullptr, m_ConstantBuffer.GetAddressOf())))
	{
		return false;
	}

	return true;
}
