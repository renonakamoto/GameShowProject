#ifndef IDLE_STATE_H_
#define IDLE_STATE_H_

#include "PlayerState.h"

class IdleState : public PlayerState
{
public:
	static IdleState* GetInstance()
	{
		static IdleState instance;
		return &instance;
	}

	PlayerState* CheckState(Player* player_) override;

	void Update(Player* player_) override;

	void Enter(Player* player_) override;

private:
	IdleState()
	{}

	~IdleState()
	{}
	
};

#endif