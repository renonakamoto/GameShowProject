#ifndef PlayerStandUp_H_
#define PlayerStandUp_H_

#include "PlayerStateBase.h"

class PlayerStandUp : public PlayerStateBase
{
public:
	static PlayerStandUp* GetInstance()
	{
		static PlayerStandUp instance;
		return &instance;
	}

	virtual void Init(Player* player_);

	virtual void Update(Player* player_);

	virtual PlayerMotionList GetType()const { return PlayerMotionList::Stand_Up; }

private:
	bool m_FinishedMotionion;
};

#endif