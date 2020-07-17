#ifndef PLAYERSPRINT_H_
#define PLAYERSPRINT_H_

#include "PlayerStateBase.h"

class PlayerSprint : public PlayerStateBase
{
public:
	static PlayerSprint* GetInstance()
	{
		static PlayerSprint instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Walk; }

};

#endif