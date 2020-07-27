#ifndef CONFIGUI_H_
#define CONFIGUI_H_

#include "../UI.h"

/**
* @brief コンフィグUIリスト
*/
enum class CONFIG_UI_LIST
{
	CONFIG_UI_CONFIG,					//! コンフィグ
	CONFIG_UI_MOUSE_NORMAL,				//! 通常マウス
	CONFIG_UI_MOUSE_REVERSE,			//! 反転マウス
	CONFIG_UI_SELECTING_MOUSE_NORMAL,	//! 選択状態の通常マウス
	CONFIG_UI_SELECTING_MOUSE_REVERSE,	//! 選択状態の反転マウス
	CONFIG_UI_RETURN,					//! 戻る

	CONFIG_UI_MAX,						//! UIの数
};

/**
* @brief コンフィグUIクラス
*/
class ConfigUI : public UI
{
public:
	/**
	* @brief コンストラクタ
	*/
	ConfigUI();

	/**
	* @brief デストラクタ
	*/
	~ConfigUI();

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
	bool IsSelect(CONFIG_UI_LIST id_);

private:
	UI_PARAMETER m_ConfigUIList[static_cast<int>(CONFIG_UI_LIST::CONFIG_UI_MAX)];	//! ConfigUiList

};

#endif