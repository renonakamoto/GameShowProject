#ifndef TURN_H_
#define TURN_H_

#include "..//..//EnemyBase.h"
#include "..//State.h"

class Turn : public State
{
public:
	Turn() {}
	virtual ~Turn() {}
	void Update(Enemybase* enemy_) override;
};

#endif // !TURN_H_