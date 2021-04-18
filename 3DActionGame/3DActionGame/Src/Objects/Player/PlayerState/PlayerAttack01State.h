#ifndef PLAYER_ATTACK01_STATE_H_
#define PLAYER_ATTACK01_STATE_H_

#include "PlayerState.h"
#include "../../../Model/FbxStorage.h"

/**
* @brief プレイヤーの攻撃1状態を管理するクラス
*/
class PlayerAttack01State : public PlayerState
{
public:
	/**
	* @fn static PlayerAttack01State* GetInstance()
	* @brief インスタンスを返す関数
	* @return PlayerAttack01State* インスタンスのポインタ
	*/
	static PlayerAttack01State* GetInstance()
	{
		static PlayerAttack01State instance;
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
	* @brief プレイヤーが攻撃状態時の更新を行う関数
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
	PlayerAttack01State() :
		m_AttackFrame(30)
	{
	}

	/**
	* @brief デストラクタ
	*/
	~PlayerAttack01State()
	{}

private:
	const int m_AttackFrame;	//! 攻撃を与える瞬間のフレーム数

};

#endif