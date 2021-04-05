#include "IdleState.h"
#include "../Player.h"
#include "../../../Engine/InputManager.h"
#include "RunState.h"
#include "Attack01State.h"

PlayerState* IdleState::CheckState(Player* player_)
{
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_W) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_A) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_S) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_D))
	{
		return RunState::GetInstance();
	}
	else if (InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		return Attack01State::GetInstance();
	}

	return IdleState::GetInstance();
}

void IdleState::Update(Player* player_)
{
}

void IdleState::Enter(Player* player_)
{
	player_->SetMotion("Idle");
}
