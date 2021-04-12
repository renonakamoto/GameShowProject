﻿#ifndef ATTACK01_STATE_H_
#define ATTACK01_STATE_H_

#include "PlayerState.h"
#include "../../../Model/FbxStorage.h"

class Attack01State : public PlayerState
{
public:
	static Attack01State* GetInstance()
	{
		static Attack01State instance;
		return &instance;
	}

	PlayerState* CheckState(Player* player_) override;

	void Update(Player* player_) override;

	void Enter(Player* player_) override;

private:
	Attack01State() :
		m_Count(0),
		m_AttackFrame(64)
	{
	}

	~Attack01State()
	{}

private:
	int m_Count;
	const int m_AttackFrame;

};

#endif