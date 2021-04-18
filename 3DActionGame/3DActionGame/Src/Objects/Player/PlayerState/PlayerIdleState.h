#ifndef PLAYER_IDLE_STATE_H_
#define PLAYER_IDLE_STATE_H_

#include "PlayerState.h"

/**
* @brief プレイヤーの待機状態を管理するクラス
*/
class PlayerIdleState : public PlayerState
{
public:
	/**
	* @fn static PlayerIdleState* GetInstance()
	* @brief インスタンスを返す関数
	* @return PlayerIdleState* インスタンスのポインタ
	*/
	static PlayerIdleState* GetInstance()
	{
		static PlayerIdleState instance;
		return &instance;
	}

	/**
	* @fn PlayerState* CheckState(Player* enemy_)
	* @brief 状態を確認して適切な状態を返す関数
	* @param[in] player_ プレイヤークラスのポインタ
	* @return Player* プレイヤーの状態クラスのポインタを返す
	*/
	PlayerState* CheckState(Player* player_) override;

	/**
	* @fn void Update(Player* player_)
	* @brief プレイヤーが待機状態時の更新を行う関数
	* @param[in] player_ プレイヤークラスのポインタ
	*/
	void Update(Player* player_) override;

	/**
	* @fn void Enter(Player* player_)
	* @brief 状態が切り替わった際の初期化関数
	* @param[in] player_ プレイヤークラスのポインタ
	* @details 状態が切り替わった時に1度だけ呼び出す
	*/
	void Enter(Player* player_) override;

private:
	/**
	* @brief コンストラクタ
	*/
	PlayerIdleState()
	{}

	/**
	* @brief デストラクタ
	*/
	~PlayerIdleState()
	{}
	
};

#endif