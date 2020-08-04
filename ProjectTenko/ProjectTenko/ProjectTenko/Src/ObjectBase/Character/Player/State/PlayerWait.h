#ifndef PLAYERWAIT_H_
#define PLAYERWAIT_H_

#include "PlayerStateBase.h"

class PlayerWait : public PlayerStateBase
{
public:
	static PlayerWait* GetInstance()
	{
		static PlayerWait instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Wait; }

};

#endif