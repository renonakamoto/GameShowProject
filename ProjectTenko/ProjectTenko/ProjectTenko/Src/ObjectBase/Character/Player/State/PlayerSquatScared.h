#ifndef PLAYERSQUATSCARED_H_
#define PLAYERSQUATSCARED_H_

#include "PlayerStateBase.h"

class PlayerSquatScared	: public PlayerStateBase
{
public:
	static PlayerSquatScared* GetInstance()
	{
		static PlayerSquatScared instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Squat_Scared; }

private:
	bool m_FinishedMotionion;

};

#endif