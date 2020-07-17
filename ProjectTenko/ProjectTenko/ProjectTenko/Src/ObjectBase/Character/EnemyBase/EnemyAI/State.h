#ifndef STATE_H_
#define STATE_H_

#include "..//EnemyBase.h"

class Enemybase;

class State
{
public:
	/**
	* @biref コンストラクタ
	*/
	State() { }
	
	/**
	* @biref デストラクタ
	*/
	virtual ~State() { }

	virtual void Update(Enemybase* enemy_) = 0;
};

#endif // !STATE_H_
