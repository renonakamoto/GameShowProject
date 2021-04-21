#include "../Player.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerAttack01State.h"
#include "../../../Engine/Engine.h"

PlayerState* PlayerIdleState::CheckState(Player* player_)
{
	// 移動キーが押されたら移動状態へ遷移
	if (INPUT->GetKey(KeyInfo::Key_W) ||
		INPUT->GetKey(KeyInfo::Key_A) ||
		INPUT->GetKey(KeyInfo::Key_S) ||
		INPUT->GetKey(KeyInfo::Key_D))
	{
		return PlayerRunState::GetInstance();
	}
	// 左クリックが押されたら攻撃状態へ遷移
	else if (INPUT->GetMouseDown(MouseButton::Left))
	{
		return PlayerAttack01State::GetInstance();
	}

	// 待機状態
	return PlayerIdleState::GetInstance();
}

void PlayerIdleState::Update(Player* player_)
{
}

void PlayerIdleState::Enter(Player* player_)
{
	player_->SetMotion("Idle");
}
