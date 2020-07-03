#ifndef STATE_H_
#define STATE_H_

#include "..//EnemyBase.h"

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

	virtual void Init(Enemybase* enemy_);
	virtual void Update(Enemybase* enemy_);
};

#endif // !STATE_H_
