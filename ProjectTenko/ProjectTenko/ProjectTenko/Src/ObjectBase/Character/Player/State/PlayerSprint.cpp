#include "PlayerSprint.h"
#include "../Player.h"
#include "../../../../Engine/Input/InputManager.h"
#include "PlayerSquatWalk.h"
#include "PlayerWait.h"

void PlayerSprint::Init(Player* player_)
{
	player_->SetIsSquad(false);
}

void PlayerSprint::Update(Player* player_)
{
	// 止まったら「待機」に遷移
	if (!player_->IsMove())
	{
		player_->ChangeState(PlayerWait::GetInstance());
	}

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSquatWalk::GetInstance());
	}
	

	player_->Motion(PlayerMotionList::Walk);

}
