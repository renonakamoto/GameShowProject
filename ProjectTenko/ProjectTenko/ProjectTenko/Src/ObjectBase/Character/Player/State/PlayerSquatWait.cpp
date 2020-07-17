#include "PlayerSquatWait.h"
#include "../Player.h"
#include "../../../../Engine/Input/InputManager.h"
#include "PlayerSquatWalk.h"
#include "PlayerStandUp.h"

void PlayerSquatWait::Init(Player* player_)
{
	player_->SetIsSquad(true);
}

void PlayerSquatWait::Update(Player* player_)
{
	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerStandUp::GetInstance());
	}

	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSquatWalk::GetInstance());
	}


	player_->Motion(PlayerMotionList::Squat_Wait);

}