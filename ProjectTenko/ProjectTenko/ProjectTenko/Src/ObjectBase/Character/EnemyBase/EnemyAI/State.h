#ifndef STATE_H_
#define STATE_H_

#include "..//EnemyBase.h"

class Enemybase;

class State
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	State() { }
	
	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~State() { }

	virtual void Update(Enemybase* enemy_) = 0;
};

#endif // !STATE_H_
