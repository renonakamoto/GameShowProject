#ifndef PLAYERSQUAT_H_
#define PLAYERSQUAT_H_

#include "PlayerStateBase.h"

class PlayerSquat : public PlayerStateBase
{
public:
	static PlayerSquat* GetInstance()
	{
		static PlayerSquat instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Squat; }

private:
	bool m_FinishedMotionion;
};

#endif