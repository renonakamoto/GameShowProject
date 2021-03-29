#ifndef RUN_STATE_H_
#define RUN_STATE_H_

#include "PlayerState.h"

class RunState : public PlayerState
{
public:
	static RunState* GetInstance()
	{
		static RunState instance;
		return &instance;
	}

	PlayerState* CheckState(Player* player_) override;

	void Update(Player* player_) override;

	void Enter(Player* player_) override;
	
private:
	RunState()
	{}

	~RunState()
	{}
};

#endif