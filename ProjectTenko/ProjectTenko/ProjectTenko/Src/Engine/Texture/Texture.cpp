#include "Texture.h"
#include "../../Utility/3DHelper.h"
#include "../../Utility/2DHelper.h"
#include "../Graphics/DirectGraphics.h"
#include <d3dx9.h>

#define	TEXTURE_MAX	1000

struct LoadedTextureInfo
{
	char		filename[MAX_PATH];
	int			count;
	TextureData	texData;
};
static LoadedTextureInfo g_loadedTextures[TEXTURE_MAX] = {};

// �e�N�X�`���[�̓ǂݍ���
static const TextureData* LoadTexture(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (strcmp(pInfo->filename, pFileName) == 0)
		{
			pInfo->count++;
			return &pInfo->texData;
		}
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count != 0) continue;

		IDirect3DTexture9 * pTexture;
		D3DXIMAGE_INFO info;
		LPDIRECT3DDEVICE9 device = THE_GRAPHICS->GetD3DDevice();
		// �t�@�C������e�N�X�`���[�𐶐�����
		HRESULT hr = D3DXCreateTextureFromFileExA(
			THE_GRAPHICS->GetD3DDevice(),	// Direct3DDevice
			pFileName,				// �t�@�C����
			D3DX_DEFAULT,			// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
			D3DX_DEFAULT,			// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
			1,						// �~�b�v�}�b�v�̐�
			0,						// �g�p�p�r
			D3DFMT_A8R8G8B8,		// �t�H�[�}�b�g
			D3DPOOL_MANAGED,		// �������̊Ǘ��ݒ�
			D3DX_FILTER_NONE,		// �t�B���^�[�ݒ�
			D3DX_DEFAULT,			// �~�b�v�}�b�v�t�B���^�[�̐ݒ�
			0x00000000,				// �J���[�L�[
			&info,					// �摜���
			NULL,					// �p���b�g�f�[�^
			&pTexture);				// ���������e�N�X�`���[�̊i�[��
		if (SUCCEEDED(hr))
		{
			D3DSURFACE_DESC desc;
			// ���������e�N�X�`���[�̏����擾
			pTexture->GetLevelDesc(0, &desc);
			// �e�N�X�`���[���̐ݒ�
			pInfo->texData.pTexture  = pTexture;
			pInfo->texData.srcWidth  = info.Width;
			pInfo->texData.srcHeight = info.Height;
			pInfo->texData.width  = desc.Width;
			pInfo->texData.height = desc.Height;

			return &pInfo->texData;
		}
		break;
	}
	return NULL;
}


// �e�N�X�`���[�̓ǂݍ���
bool LoadTexture(const char* pFileName, TextureData* pOut)
{
	if (pOut == NULL) return false;

	const TextureData * pData = LoadTexture(pFileName);
	if (pData == NULL) return false;

	*pOut = *pData;
	return true;
}

// �e�N�X�`���[�̉��
void ReleaseTexture(TextureData * pTextureData)
{
	if (pTextureData == NULL) return;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (pInfo->texData.pTexture == pTextureData->pTexture)
		{
			pInfo->count--;
			if (pInfo->count == 0)
			{
				ZeroMemory(pInfo, sizeof(*pInfo));

				SAFE_RELEASE(pTextureData->pTexture);
			}
		}
	}
}

MyTextureManager::TextureManager::~TextureManager()
{
	this->AllRelease();
}

bool MyTextureManager::TextureManager::Load(std::string key_)
{
	// �e�N�X�`��������
	std::map<std::string, TextureData*>::iterator itr = m_TextureMap.find(key_);
	// ���������ꍇ�������^�[��
	if (itr != m_TextureMap.end()) { return true; }

	// ������Ȃ������ꍇ
	LPDIRECT3DTEXTURE9 tex_info = nullptr;
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFileA(key_.c_str(), &info);

	HRESULT hr = D3DXCreateTextureFromFileExA(
		THE_GRAPHICS->GetD3DDevice(),									// Direct3DDevice
		key_.c_str(),							// �t�@�C����
		info.Width,								// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
		info.Height,							// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
		1,										// �~�b�v�}�b�v�̐�
		0,										// �g�p�p�r
		D3DFMT_UNKNOWN,						// �t�H�[�}�b�g
		D3DPOOL_MANAGED,						// �������̊Ǘ��ݒ�
		D3DX_DEFAULT,							// �t�B���^�[�ݒ�
		D3DX_DEFAULT,							// �~�b�v�}�b�v�t�B���^�[�̐ݒ�
		0x0000ff00,								// �J���[�L�[
		nullptr,								// �摜���
		nullptr,								// �p���b�g�f�[�^
		&tex_info);

	if (SUCCEEDED(hr))
	{
		D3DSURFACE_DESC desc;
		// ���������e�N�X�`���[�̏����擾
		tex_info->GetLevelDesc(0, &desc);
		// �e�N�X�`���[���̐ݒ�
		m_TextureMap[key_] = new TextureData();
		m_TextureMap[key_]->pTexture  = tex_info;
		m_TextureMap[key_]->width	  = info.Width;
		m_TextureMap[key_]->height	  = info.Height;
		m_TextureMap[key_]->srcWidth  = info.Width;
		m_TextureMap[key_]->srcHeight = desc.Height;
		
		return true;
	}

	return false;
}

TextureData* MyTextureManager::TextureManager::GetTexturue(std::string key_)
{
	// �e�N�X�`��������
	std::map<std::string, TextureData*>::iterator itr = m_TextureMap.find(key_);

	// ���������ꍇ
	if (itr != m_TextureMap.end()) { return itr->second; }
	
	// ������Ȃ������ꍇ�V�����}�b�v�ɒǉ�����
	bool success = this->Load(key_);

	// ����
	if (success) {
		return m_TextureMap[key_];
	}
	// ���s
	else{ 
		return nullptr;
	}
}


void MyTextureManager::TextureManager::Release(std::string key_)
{
	if (m_TextureMap.empty() == true)  return;
	if (m_TextureMap[key_] == nullptr) return;
	m_TextureMap[key_] = nullptr;
}

void MyTextureManager::TextureManager::AllRelease()
{
	if (m_TextureMap.empty() == true)  return;

	for (auto& itr : m_TextureMap)
	{
		delete itr.second;
		itr.second = nullptr;
	}

	m_TextureMap.clear();
}

void MyTextureManager::TextureManager::DrawTexture(float posX_, float posY_, std::string key_)
{
	float width = m_TextureMap[key_]->width;
	float height = m_TextureMap[key_]->height;

	CustomVertex v[4] =
	{
		{posX_, posY_, 0.0f, 1.0f, 0.0f, 0.0f},
		{posX_ + width, posY_, 0.0f, 1.0f, 1.0f, 0.0f},
		{posX_ + width, posY_ + height, 0.0f, 1.0f, 1.0f, 1.0f},
		{posX_, posY_ + height, 0.0f, 1.0f, 0.0f, 1.0f},
	};

	THE_GRAPHICS->GetD3DDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	THE_GRAPHICS->GetD3DDevice()->SetTexture(0, m_TextureMap[key_]->pTexture);
	THE_GRAPHICS->GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));

}
