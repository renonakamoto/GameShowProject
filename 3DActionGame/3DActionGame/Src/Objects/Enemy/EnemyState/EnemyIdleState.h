#ifndef ENEMY_IDLE_STATE_H_
#define ENEMY_IDLE_STATE_H_

#include "EnemyState.h"

class EnemyIdleState : public EnemyState
{
public:
	static EnemyIdleState* GetInstance()
	{
		static EnemyIdleState instance;
		return &instance;
	}

	EnemyState* CheckState(Enemy* enemy_) override;

	void Update(Enemy* enemy_) override;

	void Enter(Enemy* enemy_) override;

private:
	EnemyIdleState()
	{}

	~EnemyIdleState()
	{}
};

#endif