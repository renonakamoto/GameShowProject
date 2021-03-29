#include "IdleState.h"
#include "../Player.h"
#include "../../../Engine/InputManager.h"
#include "RunState.h"
#include "Attack01State.h"

PlayerState* IdleState::CheckState(Player* player_)
{
	if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_W) ||
		InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_A) ||
		InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_S) ||
		InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_D))
	{
		return RunState::GetInstance();
	}
	else if (InputManager::GetInstance()->GetMouse(MouseButton::Left))
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
