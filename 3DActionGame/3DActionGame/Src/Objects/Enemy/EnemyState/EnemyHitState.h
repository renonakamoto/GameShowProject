#ifndef ENEMY_HIT_STATE_H_
#define ENEMY_HIT_STATE_H_

#include "EnemyState.h"

class EnemyHitState : public EnemyState
{
public:
	static EnemyHitState* GetInstance()
	{
		static EnemyHitState instance;
		return &instance;
	}

	EnemyState* CheckState(Enemy* enemy_) override;

	void Update(Enemy* enemy_) override;

	void Enter(Enemy* enemy_) override;

private:
	EnemyHitState()
	{}

	~EnemyHitState()
	{}
};

#endif