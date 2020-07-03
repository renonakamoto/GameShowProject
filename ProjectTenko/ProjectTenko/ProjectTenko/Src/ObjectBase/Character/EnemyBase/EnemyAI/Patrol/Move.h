#ifndef MOVE_H_
#define MOVE_H_

#include "..//..//EnemyBase.h"
#include "..//State.h"

class Move : public State
{
public:
	Move() {}
	virtual ~Move() {}

	virtual void Update(Enemybase* enemy_) override;
};

#endif // !MOVE_H_