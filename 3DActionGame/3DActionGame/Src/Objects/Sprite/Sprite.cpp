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

	// 入力レイアウトを設定
	context->IASetInputLayout(m_InputLayout.Get());

	// 頂点バッファの登録
	UINT stride = sizeof(Vertex2D);
	UINT offset = 0;
	context->IASetVertexBuffers(0U, 1U, m_TextureData.VertexBuffer.GetAddressOf(), &stride, &offset);

	// インデックスバッファの登録
	context->IASetIndexBuffer(m_TextureData.IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0U);

	// プリミティブタイプの設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ワールド行列の設定
	int client_width  = WINDOW->GetClientWidth();
	int client_height = WINDOW->GetClientHeight();
	m_ConstantBufferData.World = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(1.f - (pos_.x / (client_width / 2)), 1.f - (pos_.y / (client_height / 2)), pos_.z));

	// 正射影行列の設定
	m_ConstantBufferData.Projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, client_width, client_height, 0.0f, -1.0f, 1.0f));
	context->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_ConstantBufferData, 0U, 0U);

	// 定数バッファの設定
	context->VSSetConstantBuffers(0U, 1U, m_ConstantBuffer.GetAddressOf());

	// シェーダーの設定
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0U);

	// テクスチャをシェーダに登録
	ID3D11SamplerState* sampler = GRAPHICS->GetSSamplerState();
	context->PSSetSamplers(0U, 1U, &sampler);
	context->PSSetShaderResources(0U, 1U, m_TextureData.Texture.GetAddressOf());

	context->PSSetShaderResources(1U, 1U, TEX_MANAGER->GetTexture("BlurMap")->Texture.GetAddressOf());

	// インデックスバッファで描画
	context->DrawIndexed(6U, 0U, 0U);
}

bool Sprite::CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	float tex_width = static_cast<float>(data_.Width);
	float tex_height = static_cast<float>(data_.Height);

	// 四角形ポリゴンの頂点を定義
	Vertex2D vertices[4]{
		{{0.0f,		 0.0f,		 0.0f}, {0.0f, 0.0f}},	// 左上頂点
		{{tex_width, 0.0f,		 0.0f}, {1.0f, 0.0f}},	// 右上頂点
		{{0.0f,		 tex_height, 0.0f}, {0.0f, 1.0f}},	// 左下頂点
		{{tex_width, tex_height, 0.0f}, {1.0f, 1.0f}}	// 右下頂点
	};

	// バッファの設定
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = sizeof(Vertex2D) * 4;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;

	// リソースの設定
	D3D11_SUBRESOURCE_DATA init_data;
	ZeroMemory(&init_data, sizeof(init_data));
	init_data.pSysMem = vertices;

	// 頂点バッファの作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,										// バッファ情報
		&init_data,										    // リソース情報
		data_.VertexBuffer.GetAddressOf())))								// 作成されたバッファの格納先
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

	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = sizeof(DWORD) * 6;	// バッファのサイズ
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;				// 使用方法
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;			// BIND設定
	buffer_desc.CPUAccessFlags = 0;								// リソースへのCPUのアクセス権限についての設定

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = index;	// バッファの中身の設定

	// バッファ作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,			// バッファ情報
		&init_data,			// リソース情報
		data_.IndexBuffer.GetAddressOf())))	// 作成されたバッファの格納先
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

	//頂点レイアウト作成
	if (FAILED(device_->CreateInputLayout(
		vertex_desc,				// レイアウト設定
		ARRAYSIZE(vertex_desc),		// 配列サイズ
		m_VertexShader->GetData(),	// レイアウトと関連付ける頂点シェーダのデータ
		m_VertexShader->GetSize(),	// レイアウトと関連付ける頂点シェーダのサイズ
		m_InputLayout.GetAddressOf())))			// 作成された頂点レイアウトの格納先
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
