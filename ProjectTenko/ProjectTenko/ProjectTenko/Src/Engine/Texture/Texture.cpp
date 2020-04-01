#include "Texture.h"
#include "../../Utility/3DHelper.h"
#include "../Graphics/DirectGraphics.h"

typedef MySingletonTemplate::SingletonTemplate<MyDirectGraphics::DirectGraphics> DirectGraphics;

#ifndef THE_GRAPHICS DirectGraphics::GetInstance()

#define THE_GRAPHICS DirectGraphics::GetInstance()

#endif

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
			pInfo->texData.pTexture = pTexture;
			pInfo->texData.srcWidth = info.Width;
			pInfo->texData.srcHeight = info.Height;
			pInfo->texData.width = desc.Width;
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