#ifndef ENEMY_DEATH_STATE_H_
#define ENEMY_DEATH_STATE_H_

#include "EnemyState.h"

class EnemyDeathState : public EnemyState
{
public:
	static EnemyDeathState* GetInstance()
	{
		static EnemyDeathState instance;
		return &instance;
	}

	EnemyState* CheckState(Enemy* enemy_) override;

	void Update(Enemy* enemy_) override;

	void Enter(Enemy* enemy_) override;

private:
	EnemyDeathState()
	{}

	~EnemyDeathState()
	{}

};

#endif