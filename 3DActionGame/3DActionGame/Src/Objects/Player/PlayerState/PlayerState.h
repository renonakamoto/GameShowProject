#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

class Player;

/**
* @brief プレイヤーの状態基底クラス
*/
class PlayerState
{
public:
	/**
	* @brief コンストラクタ
	*/
	PlayerState()
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~PlayerState()
	{}

	/**
	* @fn PlayerState* CheckState(Player* player_)
	* @brief 状態を確認して適切な状態を返す関数
	* @param[in] player_ プレイヤークラスのポインタ
	* @return PlayerState* プレイヤーの状態クラスのポインタを返す
	*/
	virtual PlayerState* CheckState(Player* player_) = 0;

	/**
	* @fn void Update(Player* player_)
	* @brief プレイヤーの各状態時の更新を行う関数
	* @param[in] player_ プレイヤークラスのポインタ
	* @details 派生先で状態時の更新を行う
	*/
	virtual void Update(Player* player_) = 0;

	/**
	* @fn void Enter(Player* player_)
	* @brief 状態が切り替わった際の初期化関数
	* @param[in] player_ プレイヤークラスのポインタ
	* @details 派生先で状態の初期化を行う
	*/
	virtual void Enter(Player* player_) = 0;
};

#endif