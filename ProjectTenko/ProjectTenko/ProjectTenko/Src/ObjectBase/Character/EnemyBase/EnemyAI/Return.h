#ifndef RETURN_H_
#define RETURN_H_

#include "..//EnemyBase.h"
#include "State.h"

class Return : public State
{
public:
	Return() {}
	virtual ~Return() {}

	void Update(Enemybase* enemy_) override;
};

#endif // !RETURN_H_
