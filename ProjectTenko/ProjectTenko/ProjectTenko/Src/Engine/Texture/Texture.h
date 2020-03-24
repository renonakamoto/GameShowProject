#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <d3dx9.h>

// テクスチャーデータ
struct TextureData
{
	UINT				width;		// テクスチャーの幅
	UINT				height;		// テクスチャーの高さ
	UINT				srcWidth;	// 画像の幅
	UINT				srcHeight;	// 画像の高さ
	IDirect3DTexture9* pTexture;	// 生成したテクスチャーのポインタ
};

// テクスチャーの読み込み
bool LoadTexture(const char* pFileName, TextureData* pOut);

// テクスチャーの解放
void ReleaseTexture(TextureData* pTextureData);

#endif