#ifndef ENEMY_DEATH_STATE_H_
#define ENEMY_DEATH_STATE_H_

#include "EnemyState.h"

/**
* @brief エネミーの死亡状態時を管理する
*/
class EnemyDeathState : public EnemyState
{
public:
	/**
	* @fn static EnemyDeathState* GetInstance()
	* @brief インスタンスを返す関数
	* @return EnemyDeathState* インスタンスのポインタ
	*/
	static EnemyDeathState* GetInstance()
	{
		static EnemyDeathState instance;
		return &instance;
	}

	/**
	* @fn EnemyState* CheckState(Enemy* enemy_)
	* @brief 状態を確認して適切な状態を返す関数
	* @param[in] enemy_ エネミークラスのポインタ
	* @return EnemyState* エネミーの状態クラスのポインタを返す
	*/
	EnemyState* CheckState(Enemy* enemy_) override;

	/**
	* @fn void Update(Enemy* enemy_)
	* @brief エネミーの死亡状態時の更新を行う関数
	* @param[in] enemy_ エネミークラスのポインタ
	*/
	void Update(Enemy* enemy_) override;

	/**
	* @fn void Enter(Enemy* enemy_)
	* @brief 状態が切り替わった際の初期化関数
	* @param[in] enemy_ エネミークラスのポインタ
	* @details 状態が切り替わった時に1度だけ呼び出す
	*/
	void Enter(Enemy* enemy_) override;

private:
	/**
	* @brief コンストラクタ
	*/
	EnemyDeathState()
	{}

	/**
	* @brief デストラクタ
	*/
	~EnemyDeathState()
	{}
};

#endif