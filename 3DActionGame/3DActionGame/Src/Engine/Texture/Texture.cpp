#include "../../DirectXTex/DirectXTex.h"
#include <D3D11.h>
#include <codecvt>
#include "Texture.h"
#include "../../Utility/Utility.h"


bool TextureManager::Init(ID3D11Device* device_)
{
	// nullチェック
	if (device_ == nullptr) return false;

	// シェーダーの作成
	if (CreateShader(device_) == false)
	{
		return false;
	}
	// 入力レイアウトの作成
	if (CreateInputLayout(device_) == false)
	{
		return false;
	}

	// 定数バッファの作成
	if (CreateConstantBuffer(device_) == false)
	{
		return false;
	}

	if (CreateSamplerState(device_) == false)
	{
		return false;
	}

	return true;
}

bool TextureManager::Load(const char* fileName_, std::string keyword_)
{
	// すでにキーが存在する場合は読み込みが終わっているので早期リターン
	//for (auto itr = m_Texture.begin(); itr != m_Texture.end(); ++itr)
	//{
	//	if (itr->first == keyword_) return true;
	//}

	TextureData tex_data;
	
	// デバイスを取得
	ID3D11Device* device = DirectGraphics::GetInstance()->GetDevice();

	// ファイル分解
	char buffer[256];
	ZeroMemory(buffer, sizeof(char) * 256);
	memcpy(buffer, fileName_, sizeof(char) * 256);

	Replace('\\', '/', buffer);
	std::string replace_file_name = buffer;

	// /で分解
	std::vector<std::string> split_list = Split(buffer, '/');

	std::string path = fileName_;
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wstr_file_name = cv.from_bytes(path);
	
	const char* extension = "";
	DirectX::TexMetadata  metadata;
	DirectX::ScratchImage image;
	HRESULT hr;

	// 拡張子を保存する
	for (size_t i = strlen(fileName_); i != 0; --i)
	{
		if (fileName_[i - 1] == '.') extension = &fileName_[i];
	}

	// DDSファイルの読み込み
	if (strcmp(extension, "dds") == 0)
	{
		hr = DirectX::LoadFromDDSFile(wstr_file_name.c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, &metadata, image);
	}
	// TGAファイルの読み込み
	else if (strcmp(extension, "tga") == 0)
	{
		hr = DirectX::LoadFromTGAFile(wstr_file_name.c_str(), &metadata, image);
	}
	// WICファイル(bmp,jpg,png)の読み込み
	else
	{
		hr = DirectX::LoadFromWICFile(wstr_file_name.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	}

	// 読み込みに失敗したとき
	if (FAILED(hr))
	{
		return false;
	}

	if (FAILED(DirectX::CreateShaderResourceView(
		device,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&tex_data.Texture)))
	{
		return false;
	}

	tex_data.Width  = metadata.width;
	tex_data.Height = metadata.height;

	if (CreateVertexBuffer(tex_data, device) == false)
	{
		return false;
	}
	
	if (CreateIndexBuffer(tex_data, device) == false)
	{
		return false;
	}

	m_Texture[keyword_] = tex_data;

	return true;
}

void TextureManager::Render(std::string keyword_, DirectX::XMFLOAT3 pos_)
{
	ID3D11DeviceContext* context = DirectGraphics::GetInstance()->GetContext();
	ID3D11Device* device = DirectGraphics::GetInstance()->GetDevice();

	TextureData* texture = &m_Texture[keyword_];

	// 入力レイアウトを設定
	context->IASetInputLayout(m_InputLayout);

	// 頂点バッファの登録
	UINT stride = sizeof(Vertex2D);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &texture->VertexBuffer, &stride, &offset);
	// インデックスバッファの登録
	context->IASetIndexBuffer(texture->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// プリミティブタイプの設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_ConstantBufferData.World		= DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(1.f - (0.f / 640.f), 1.f - (0.f / 360.f), pos_.z));
	m_ConstantBufferData.Projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280, 720, 0.0f, 0.0f, 1.0f));
	context->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &m_ConstantBufferData, 0, 0);
	
	// GPUにバッファをセット
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0);
	context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0);
	context->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

	// テクスチャをシェーダに登録
	context->PSSetSamplers(0, 1, &m_SamplerState);
	context->PSSetShaderResources(0, 1, &texture->Texture);

	// インデックスバッファで描画
	context->DrawIndexed(6, 0, 0);
}

bool TextureManager::CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	float tex_width  = static_cast<float>(data_.Width);
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
	buffer_desc.ByteWidth	    = sizeof(Vertex2D) * 4;
	buffer_desc.Usage			= D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags  = 0;
	
	// リソースの設定
	D3D11_SUBRESOURCE_DATA init_data;
	ZeroMemory(&init_data, sizeof(init_data));
	init_data.pSysMem = vertices;

	// 頂点バッファの作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,										// バッファ情報
		&init_data,										    // リソース情報
		&data_.VertexBuffer)))								// 作成されたバッファの格納先
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
{
	if (device_ == nullptr) return false;

	
	WORD index[]{
		0, 1, 2,
		2, 1, 3
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth		= sizeof(DWORD) * 6;	// バッファのサイズ
	buffer_desc.Usage			= D3D11_USAGE_DEFAULT;				// 使用方法
	buffer_desc.BindFlags		= D3D11_BIND_INDEX_BUFFER;			// BIND設定
	buffer_desc.CPUAccessFlags  = 0;								// リソースへのCPUのアクセス権限についての設定

	D3D11_SUBRESOURCE_DATA init_data;
	init_data.pSysMem = index;	// バッファの中身の設定
	
	// バッファ作成
	if (FAILED(device_->CreateBuffer(
		&buffer_desc,			// バッファ情報
		&init_data,			// リソース情報
		&data_.IndexBuffer)))	// 作成されたバッファの格納先
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateShader(ID3D11Device* device_)
{
	m_VertexShader = new VertexShader();
	if (m_VertexShader->Create(device_, "Res/Shader/Tex2DVertexShader.cso") == false)
	{
		return false;
	}

	m_PixelShader = new PixelShader();
	if (m_PixelShader->Create(device_, "Res/Shader/Tex2DPixelShader.cso") == false)
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateInputLayout(ID3D11Device* device_)
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
		&m_InputLayout)))			// 作成された頂点レイアウトの格納先
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateConstantBuffer(ID3D11Device* device_)
{
	D3D11_BUFFER_DESC buffer_desc;
	buffer_desc.ByteWidth = sizeof(ConstantBuffer2D);
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	if (FAILED(device_->CreateBuffer(&buffer_desc, nullptr, &m_ConstantBuffer)))
	{
		return false;
	}

	return true;
}

bool TextureManager::CreateSamplerState(ID3D11Device* device_)
{
	// サンプラの設定
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW		= D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.BorderColor[0] = 1.0f;
	sampler_desc.BorderColor[1] = 1.0f;
	sampler_desc.BorderColor[2] = 1.0f;
	sampler_desc.BorderColor[3] = 1.0f;
	sampler_desc.MinLOD		    = 0.0f;
	sampler_desc.MaxLOD		    = D3D11_FLOAT32_MAX;

	// 作成
	if (FAILED(device_->CreateSamplerState(&sampler_desc, &m_SamplerState)))
	{
		return false;
	}

	return true;
}
