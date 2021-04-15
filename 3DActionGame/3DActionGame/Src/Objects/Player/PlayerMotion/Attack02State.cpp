#include "Attack02State.h"
#include "../Player.h"
#include "IdleState.h"

PlayerState* Attack02State::CheckState(Player* player_)
{
	if (m_Count >= m_AttackFrame) {
		m_Count = 0;
		return IdleState::GetInstance();
	}
	
	return Attack02State::GetInstance();
}

void Attack02State::Update(Player* player_)
{
	m_Count++;

	if (m_Count == 30) {
		player_->Attack();
	}
}

void Attack02State::Enter(Player* player_)
{
	player_->SetMotion("Attack02");
}
