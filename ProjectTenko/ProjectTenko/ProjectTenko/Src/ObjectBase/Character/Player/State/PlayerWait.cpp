#include "PlayerWait.h"
#include "../Player.h"
#include "PlayerSprint.h"
#include "PlayerSquat.h"
#include "../../../../Engine/Input/InputManager.h"

void PlayerWait::Init(Player* player_)
{
	player_->SetIsSquad(false);
}

void PlayerWait::Update(Player* player_)
{
	// 移動していたら走るモーションに遷移
	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSprint::GetInstance());
	}

	// Cが押されたらたらしゃがむモーションに遷移
	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSquat::GetInstance());
	}

	
	player_->Motion(PlayerMotionList::Wait);
}