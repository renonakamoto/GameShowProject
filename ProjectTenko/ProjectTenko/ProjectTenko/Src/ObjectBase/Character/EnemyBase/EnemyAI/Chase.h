#ifndef CHASE_H_
#define CHASE_H_

#include "..//EnemyBase.h"
#include "State.h"

class Chase : public State
{
public:
	Chase() {}
	virtual ~Chase() {}

	void Update(Enemybase* enemy_) override;
};

#endif // !CHASE_H_