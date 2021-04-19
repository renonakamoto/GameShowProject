#ifndef ENEMY_HIT_STATE_H_
#define ENEMY_HIT_STATE_H_

#include "EnemyState.h"

/**
* @brief エネミーがダメージを受けた状態時を管理する
*/
class EnemyHitState : public EnemyState
{
public:
	/**
	* @fn static EnemyHitState* GetInstance()
	* @brief インスタンスを返す関数
	* @return EnemyHitState* インスタンスのポインタ
	*/
	static EnemyHitState* GetInstance()
	{
		static EnemyHitState instance;
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
	* @brief エネミーがダメージを受けた状態時の更新を行う関数
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
	EnemyHitState():
		HitMotionFrameNum(29.f)
	{}

	/**
	* @brief デストラクタ
	*/
	~EnemyHitState() final
	{}

private:
	const float HitMotionFrameNum;	//! ヒットモーションのフレーム数
};

#endif