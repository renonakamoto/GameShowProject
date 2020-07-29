#ifndef POSEUI_H_
#define POSEUI_H_

#include "../UI.h"

/**
* @brief ポーズUIリスト
*/
enum class PAUSE_UI_LIST
{
	PAUSE_UI_BACKGROUND,	//! 背景
	PAUSE_UI_RETURN_GAME,	//! ゲーム戻る
	PAUSE_UI_RETURN_TITLE,	//! タイトルに戻る
	PAUSE_UI_SETTING,		//! 設定

	PAUSE_UI_MAX,			//! UIの数
};

/**
* @brief ポーズUIクラス
*/
class PauseUI : public UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	PauseUI();

	/**
	* @brief デストラクタ
	*/
	~PauseUI();

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
	bool IsSelect(PAUSE_UI_LIST id_);

private:
	UI_PARAMETER m_PoseUIList[static_cast<int>(PAUSE_UI_LIST::PAUSE_UI_MAX)];	//! PoseUiList

};

#endif