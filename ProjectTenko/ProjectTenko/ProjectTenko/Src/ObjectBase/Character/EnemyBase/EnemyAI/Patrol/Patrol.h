#ifndef MOVE_H_
#define MOVE_H_

#include "..//..//EnemyBase.h"
#include "..//State.h"

class Patrol : public State
{
public:
	Patrol() {}
	virtual ~Patrol() {}

	virtual void Update(Enemybase* enemy_) override;
};

#endif // !MOVE_H_