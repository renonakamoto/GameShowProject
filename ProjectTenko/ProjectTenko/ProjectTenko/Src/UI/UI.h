#ifndef UI_H_
#define UI_H_

#include <string>
#include <d3dx9.h>

/**
* @brief UIの基底クラス
*/
class UI
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~UI(){}

	/**
	* @brief 更新関数
	*/
	virtual void Update() = 0;

	/**
	* @brief 描画
	*/
	virtual void Draw() = 0;

protected:
	/**
	* @brief UIパラメータ構造体
	*/
	struct UI_PARAMETER
	{
		/**
		* @brief コンストラクタ
		*/
		UI_PARAMETER():
			m_Pos(D3DXVECTOR2(0.0f,0.0f)),
			m_SpriteWidth(0.0f),
			m_SpriteHeight(0.0f),
			m_TexturHandleKey("")
		{}

		/**
		* @brief コンストラクタ
		*/
		UI_PARAMETER(D3DXVECTOR2 pos_, float spriteWidth_, float spriteHeight, std::string texHandleKey):
			m_Pos(pos_),
			m_SpriteWidth(spriteWidth_),
			m_SpriteHeight(spriteHeight),
			m_TexturHandleKey(texHandleKey)
		{}

		D3DXVECTOR2 m_Pos;				//! 左上座標
		float m_SpriteWidth;			//! 横幅
		float m_SpriteHeight;			//! 縦幅
		std::string m_TexturHandleKey;	//! テクスチャキー
	};
	
};

#endif