#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <string>
#include "../../ObjectManager/Object2D.h"

/**
* @brief 背景クラス
*/
class Background : public Object2D
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] keyword_ モデルの描画ハンドル
	*/
	Background(std::string keyword_) :
		Background(keyword_, DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] keyword_ モデルの描画ハンドルキーワード
	* @param[in] pos_     描画座標 (左上原点)
	*/
	Background(std::string keyword_, DirectX::XMFLOAT3 pos_) :
		Object2D(pos_),
		m_TexKeyword(keyword_)
	{}

	/**
	* @brief デストラクタ
	*/
	~Background()
	{
		Release();
	}
	
	/**
	* @fn void Init()
	* @brief 初期化関数
	*/
	void Init()override
	{}

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details ゲームループで1フレームに一度呼ばれる
	*/
	void Update()override 
	{}

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details ゲームループで1フレームに一度呼ばれる
	*/
	void Draw()override;
	
private:

	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release()override
	{}

private:
	std::string m_TexKeyword;	//! 描画ハンドル

};

#endif