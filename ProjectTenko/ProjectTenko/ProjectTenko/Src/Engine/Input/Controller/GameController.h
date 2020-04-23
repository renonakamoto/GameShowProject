#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <map>
#include "GameButton.h"

class GameController
{
public:
	/**
	* @biref コンストラクタ
	*/
	GameController() : m_StickRad(), m_Buttons()
	{} 

	/**
	* @biref デストラクタ
	*/
	~GameController();

	/**
	* @biref 仮想コントローラーの初期化
	* 仮想コントローラーの初期化を行います
	* @return 初期化結果、成功の場合true
	*/
	bool Init();

	/**
	* @brief 仮想コントローラーの更新
	* 仮想コントローラー内のボタンの情報を更新します
	* @return 更新結果、問題があった場合false
	*/
	bool Update();

	/**
	* @biref ボタンを押した瞬間かの判定
	* 引数で指定したボタンを押した瞬間かどうか判定します
	* @return 判定結果、押した瞬間ならtrue
	* @param[in] key_ 判定したいボタン
	*/
	bool GetKeyDown(Button key_);

	/**
	* @biref ボタンを押しているかの判定
	* 引数で指定したボタンを押ているかどうか判定します
	* @return 判定結果、押しているならtrue
	* @param[in] key_ 判定したいボタン
	*/
	bool GetKey(Button key_);

	/**
	* @biref ボタンを離した瞬間かの判定
	* 引数で指定したボタンを離した瞬間かどうか判定します
	* @return 判定結果、離した瞬間ならtrue
	* @param[in] key_ 判定したいボタン
	*/
	bool GetKeyUp(Button key_);

	/**
	* @biref アナログスティックを傾けている方向の角度を取得する関数
	* 引数で指定した側のスティックが傾けられている方向を、コントローラー上を0として360度で値を返します
	* @return 傾けている角度、エラーの場合は-1を返す
	* @param[in] stick_ スティックの順、0が左
	*/
	int GetSthickRad(int stick_);

private:
	GameButton* m_Buttons[static_cast<int>(Button::MaxButtons)];
	int m_StickRad[2];
};

#endif GAMECONTROLLER_H_