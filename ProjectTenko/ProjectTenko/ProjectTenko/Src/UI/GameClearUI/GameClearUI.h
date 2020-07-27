#ifndef GAMECLEARUI_H_
#define GAMECLEARUI_H_

#include "../UI.h"

/**
* @brief ゲームクリアUIリスト
*/
enum class GAMECLEAR_UI_LIST
{
	GAMECLEAR_BACKGROUND,	//! 背景
	GAMECLEAR_UI_RETURN,	//! 戻る

	GAMECLEAR_UI_MAX,		//! UIの数
};

/**
* @brief ゲームクリアUIクラス
*/
class GameClearUI : public UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	GameClearUI();

	/**
	* @brief デストラクタ
	*/
	~GameClearUI() {}

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
	bool IsSelect(GAMECLEAR_UI_LIST id_);

private:
	UI_PARAMETER m_GameClearUIList[static_cast<int>(GAMECLEAR_UI_LIST::GAMECLEAR_UI_MAX)];	//! GameClearUiList

	bool IsLit;	//! 点滅させるための変数
};

#endif