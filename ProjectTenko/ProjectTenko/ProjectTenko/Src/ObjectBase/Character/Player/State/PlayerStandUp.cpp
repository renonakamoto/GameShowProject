#include "PlayerStandUp.h"
#include "../Player.h"
#include "PlayerWait.h"
#include "PlayerSprint.h"
#include "PlayerSquat.h"
#include "../../../../Engine/Input/InputManager.h"

void PlayerStandUp::Init(Player* player_)
{
	m_FinishedMotionion = false;
	player_->SetIsSquad(false);
}

void PlayerStandUp::Update(Player* player_)
{
	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSquat::GetInstance());
	}

	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSprint::GetInstance());
	}

	// �����オ�郂�[�V�������I�������u�ҋ@�v�ɑJ�ڂ���
	if (m_FinishedMotionion)
	{
		player_->ChangeState(PlayerWait::GetInstance());
	}


	player_->Motion(PlayerMotionList::Stand_Up, false, &m_FinishedMotionion);

}
