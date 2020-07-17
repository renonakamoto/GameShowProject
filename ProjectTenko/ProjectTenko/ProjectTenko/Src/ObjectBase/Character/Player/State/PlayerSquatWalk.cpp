#include "PlayerSquatWalk.h"
#include "../Player.h"
#include "../../../../Engine/Input/InputManager.h"
#include "PlayerSprint.h"
#include "PlayerSquatWait.h"

void PlayerSquatWalk::Init(Player* player_)
{
	player_->SetIsSquad(true);
}

void PlayerSquatWalk::Update(Player* player_)
{
	if(THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSprint::GetInstance());
	}

	// �~�܂�����u���Ⴊ�ޑҋ@�v�ɑJ��
	if (!player_->IsMove())
	{
		player_->ChangeState(PlayerSquatWait::GetInstance());
	}

	player_->Motion(PlayerMotionList::Squat_Walk);

}
