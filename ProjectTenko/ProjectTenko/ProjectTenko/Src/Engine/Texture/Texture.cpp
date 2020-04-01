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

// テクスチャーの読み込み
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
		// ファイルからテクスチャーを生成する
		HRESULT hr = D3DXCreateTextureFromFileExA(
			THE_GRAPHICS->GetD3DDevice(),	// Direct3DDevice
			pFileName,				// ファイル名
			D3DX_DEFAULT,			// 横幅(D3DX_DEFAULTでファイルから判定)
			D3DX_DEFAULT,			// 高さ(D3DX_DEFAULTでファイルから判定)
			1,						// ミップマップの数
			0,						// 使用用途
			D3DFMT_A8R8G8B8,		// フォーマット
			D3DPOOL_MANAGED,		// メモリの管理設定
			D3DX_FILTER_NONE,		// フィルター設定
			D3DX_DEFAULT,			// ミップマップフィルターの設定
			0x00000000,				// カラーキー
			&info,					// 画像情報
			NULL,					// パレットデータ
			&pTexture);				// 生成したテクスチャーの格納先
		if (SUCCEEDED(hr))
		{
			D3DSURFACE_DESC desc;
			// 生成したテクスチャーの情報を取得
			pTexture->GetLevelDesc(0, &desc);
			// テクスチャー情報の設定
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


// テクスチャーの読み込み
bool LoadTexture(const char* pFileName, TextureData* pOut)
{
	if (pOut == NULL) return false;

	const TextureData * pData = LoadTexture(pFileName);
	if (pData == NULL) return false;

	*pOut = *pData;
	return true;
}

// テクスチャーの解放
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