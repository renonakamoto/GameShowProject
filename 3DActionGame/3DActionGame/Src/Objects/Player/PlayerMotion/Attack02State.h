﻿#ifndef ATTACK02_STATE_H_
#define ATTACK02_STATE_H_

#include "PlayerState.h"

class Attack02State : public PlayerState
{
public:
	static Attack02State* GetInstance()
	{
		static Attack02State instance;
		return &instance;
	}

	PlayerState* CheckState(Player* player_) override;

	void Update(Player* player_) override;

	void Enter(Player* player_) override;

private:
	Attack02State():
		m_Count(0),
		m_AttackFrame(56)
	{}

	~Attack02State()
	{}

private:
	int m_Count;
	const int m_AttackFrame;

};

#endif