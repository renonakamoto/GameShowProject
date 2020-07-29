#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief テクスチャデータ構造体
*/
struct TextureData
{
	UINT				width;		//! テクスチャーの幅
	UINT				height;		//! テクスチャーの高さ
	UINT				srcWidth;	//! 画像の幅
	UINT				srcHeight;	//! 画像の高さ
	IDirect3DTexture9* pTexture;	//! 生成したテクスチャーのポインタ
};

// テクスチャーの読み込み
bool LoadTexture(const char* pFileName, TextureData* pOut);

// テクスチャーの解放
void ReleaseTexture(TextureData* pTextureData);

namespace MyTextureManager
{
	/**
	* @brief テクスチャーマネージャークラス
	*/
	class TextureManager
	{

		friend MySingletonTemplate::SingletonTemplate<TextureManager>;
	public:
		/**
		* @brief テクスチャーの読み込み関数
		* @param[in] key_  テクスチャに設定するキー
		* @return bool ture: 成功 false: 失敗
		*/
		bool Load(std::string key_);

		/**
		* @brief テクスチャデータ取得関数
		* @param[in] key_  テクスチャキー
		* @return TextureData* 
		*/
		TextureData* GetTexture(std::string key_);

		/**
		* @brief テクスチャ描画関数
		* @param[in] posX_  X座標
		* @param[in] posY_  Y座標
		* @param[in] key_   テクスチャに設定されているキー
		*/
		void DrawTexture(float posX_, float posY_, std::string key_);

		/**
		* @brief テクスチャ描画関数
		* @param[in] posX_  X座標
		* @param[in] posY_  Y座標
		* @param[in] tu_	tu値
		* @param[in] tv_	tv値
		* @param[in] key_   テクスチャに設定されているキー
		*/
		void DrawTexture(float posX_, float posY_, float tu_, float tv_, std::string key_);

		/**
		* @brief テクスチャ解放関数
		* @param[in] key_	テクスチャに設定されているキー
		*/
		void Release(std::string key_);

		/**
		* @brief 全てのテクスチャ解放関数(デストラクター時に呼ばれる)
		* @param[in] key_	テクスチャに設定されているキー
		*/
		void AllRelease();


	private:
		/**
		* @brief コンストラクタ
		*/
		TextureManager() {
		}

		/**
		* @brief デストラクタ
		*/
		~TextureManager();


		std::map<std::string, TextureData*> m_TextureMap;	//! テクスチャマップ

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyTextureManager::TextureManager> TextureManager;
#define THE_TEXTUREMANAGER TextureManager::GetInstance()

#endif