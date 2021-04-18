#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class Enemy;

/**
* @brief 敵の状態基底クラス
*/
class EnemyState
{
public:
	/**
	* @brief コンストラクタ
	*/
	EnemyState()
	{}

	/**
	* @brief デストラクタ
	*/
	~EnemyState()
	{}

	/**
	* @fn EnemyState* CheckState(Enemy* enemy_)
	* @brief 状態を確認して適切な状態を返す関数
	* @param[in] enemy_ エネミークラスのポインタ
	* @return EnemyState* エネミーの状態クラスのポインタを返す
	*/
	virtual EnemyState* CheckState(Enemy* enemy_) = 0;

	/**
	* @fn void Update(Enemy* enemy_)
	* @brief エネミーの各状態時の更新を行う関数
	* @param[in] enemy_ エネミークラスのポインタ
	* @details 派生先で状態時の更新を行う
	*/
	virtual void Update(Enemy* enemy_) = 0;

	/**
	* @fn void Enter(Enemy* enemy_)
	* @brief 状態が切り替わった際の初期化関数
	* @param[in] enemy_ エネミークラスのポインタ
	* @details 派生先で状態の初期化を行う
	*/
	virtual void Enter(Enemy* enemy_) = 0;
};

#endif