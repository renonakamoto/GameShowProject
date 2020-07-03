#ifndef PATROL_H_
#define PATROL_H_

#include "..//..//EnemyBase.h"
#include "..//State.h"

class Patrol : public State
{
public:
	Patrol() { }
	virtual ~Patrol() override { }

	virtual void Update(Enemybase* enemy_) override;
};

#endif // !PATROL_H_