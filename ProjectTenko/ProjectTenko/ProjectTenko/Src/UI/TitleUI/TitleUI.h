#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "../UI.h"

/**
* @brief タイトルUIリスト
*/
enum class TITLE_UI_LIST
{
	TITLE_UI_TITLE,		//! タイトル
	TITLE_UI_START,		//! スタート
	TITLE_UI_EXIT,		//! 終了
	TITLE_UI_SETTING,	//! 設定

	TITLE_UI_MAX,		//! UIの数
};

/**
* @brief TitleUI
*/
class TitleUI : public UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	TitleUI();

	/**
	* @brief デストラクタ
	*/
	~TitleUI();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Draw();

	/**
	* @brief 選択されたかどうか
	* @param[in] id_ UIのID
	* @return bool true: 選択された false: 選択されていない
	*/
	bool IsSelect(TITLE_UI_LIST id_);

private:

	UI_PARAMETER m_TitleUIList[static_cast<int>(TITLE_UI_LIST::TITLE_UI_MAX)];	//! TitleUiList

};

#endif