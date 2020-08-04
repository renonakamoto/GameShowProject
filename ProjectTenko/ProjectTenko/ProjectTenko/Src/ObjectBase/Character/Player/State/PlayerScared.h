#ifndef PlayerScared_H_
#define PlayerScared_H_

#include "PlayerStateBase.h"

class PlayerScared : public PlayerStateBase
{
public:
	static PlayerScared* GetInstance()
	{
		static PlayerScared instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Scared; }

	
};

#endif