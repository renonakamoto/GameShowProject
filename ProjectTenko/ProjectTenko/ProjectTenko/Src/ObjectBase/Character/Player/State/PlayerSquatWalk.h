#ifndef PLAYERSQUATWALK_H_
#define PLAYERSQUATWALK_H_

#include "PlayerStateBase.h"

class PlayerSquatWalk : public PlayerStateBase
{
public:
	static PlayerSquatWalk* GetInstance()
	{
		static PlayerSquatWalk instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Squat_Walk; }

};

#endif