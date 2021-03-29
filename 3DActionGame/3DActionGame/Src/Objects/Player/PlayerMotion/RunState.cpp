#include "RunState.h"
#include "../Player.h"
#include "../../../Engine/InputManager.h"
#include "Attack01State.h"
#include "IdleState.h"

PlayerState* RunState::CheckState(Player* player_)
{
	if (InputManager::GetInstance()->GetMouse(MouseButton::Left))
	{
		return Attack01State::GetInstance();
	}
	else if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_W) ||
			 InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_A) ||
			 InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_S) ||
			 InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_D))
	{
		return RunState::GetInstance();
	}

	return IdleState::GetInstance();
}

void RunState::Update(Player* player_)
{
	
}

void RunState::Enter(Player* player_)
{
	player_->SetMotion("Run");
}