#ifndef PLAYERSQUATWAIT_H_
#define PLAYERSQUATWAIT_H_

#include "PlayerStateBase.h"

class PlayerSquatWait : public PlayerStateBase
{
public:
	static PlayerSquatWait* GetInstance()
	{
		static PlayerSquatWait instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Squat_Wait; }
};

#endif