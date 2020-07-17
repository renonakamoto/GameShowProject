#include "PlayerSquat.h"
#include "../Player.h"
#include "PlayerStandUp.h"
#include "PlayerSquatWalk.h"
#include "PlayerSquatWait.h"
#include "../../../../Engine/Input/InputManager.h"

void PlayerSquat::Init(Player* player_)
{
	m_FinishedMotionion = false;
	player_->SetIsSquad(true);
}

void PlayerSquat::Update(Player* player_)
{
	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSquatWalk::GetInstance());
	}

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerStandUp::GetInstance());
	}

	// しゃがみモーションが終わったら「しゃがみ待機」に遷移
	if (m_FinishedMotionion)
	{
		player_->ChangeState(PlayerSquatWait::GetInstance());
	}

	player_->Motion(PlayerMotionList::Squat, false, &m_FinishedMotionion);

}