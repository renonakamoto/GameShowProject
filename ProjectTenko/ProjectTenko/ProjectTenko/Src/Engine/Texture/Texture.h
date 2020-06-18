#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <map>
#include <string>

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

namespace MyTextureManager
{
	class TextureManager
	{

		friend MySingletonTemplate::SingletonTemplate<TextureManager>;
	public:

		bool Load(std::string key_);

		TextureData* GetTexturue(std::string key_);

		void Release(std::string key_);

		void AllRelease();

		void DrawTexture(float posX_, float posY_, std::string key_);

		void DrawTexture(float posX_, float posY_, float tu_, float tv_, std::string key_);

	private:
		TextureManager() {
		}

		~TextureManager();

		std::map<std::string, TextureData*> m_TextureMap;

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyTextureManager::TextureManager> TextureManager;
#define THE_TEXTUREMANAGER TextureManager::GetInstance()

#endif