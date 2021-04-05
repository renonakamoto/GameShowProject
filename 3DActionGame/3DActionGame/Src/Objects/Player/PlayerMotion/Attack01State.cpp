#include "Attack01State.h"
#include "Attack02State.h"
#include "../Player.h"
#include "IdleState.h"
#include "../../../Engine/InputManager.h"

PlayerState* Attack01State::CheckState(Player* player_)
{
	if (m_Count >= m_AttackFrame) {
		m_Count = 0;
		return IdleState::GetInstance();
	}

	if (m_Count >= 40 && InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		m_Count = 0;
		return Attack02State::GetInstance();
	}

	return Attack01State::GetInstance();
}

void Attack01State::Update(Player* player_)
{
	m_Count++;
}

void Attack01State::Enter(Player* player_)
{
	player_->SetMotion("Attack01");
}
