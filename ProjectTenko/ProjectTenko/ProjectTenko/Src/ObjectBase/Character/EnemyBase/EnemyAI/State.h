#ifndef STATE_H_
#define STATE_H_

#include "..//EnemyBase.h"

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

	virtual void Init(Enemybase* enemy_);
	virtual void Update(Enemybase* enemy_);
};

#endif // !STATE_H_
