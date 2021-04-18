#include "../Player.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerAttack01State.h"
#include "../../../Engine/InputManager.h"

PlayerState* PlayerIdleState::CheckState(Player* player_)
{
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_W) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_A) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_S) ||
		InputManager::GetInstance()->GetKey(KeyInfo::Key_D))
	{
		return PlayerRunState::GetInstance();
	}
	else if (InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		return PlayerAttack01State::GetInstance();
	}

	return PlayerIdleState::GetInstance();
}

void PlayerIdleState::Update(Player* player_)
{
}

void PlayerIdleState::Enter(Player* player_)
{
	player_->SetMotion("Idle");
}
