#ifndef GAMEOVERUI_H_
#define GAMEOVERUI_H_

#include "../UI.h"

/**
* @brief ゲームオーバーUIリスト
*/
enum class GAMEOVER_UI_LIST
{
	GAMEOVER_BACKGROUND,	//! 背景
	GAMEOVER_UI_RETURN,		//! 戻る

	GAMEOVER_UI_MAX,		//! UIの数
};

/**
* @brief ゲームオーバーUIクラス
*/
class GameOverUI : public UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	GameOverUI();

	/**
	* @brief デストラクタ
	*/
	~GameOverUI() {}

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
	bool IsSelect(GAMEOVER_UI_LIST id_);

private:
	UI_PARAMETER m_GameOverUIList[static_cast<int>(GAMEOVER_UI_LIST::GAMEOVER_UI_MAX)];	//! GameOverUiList

};

#endif