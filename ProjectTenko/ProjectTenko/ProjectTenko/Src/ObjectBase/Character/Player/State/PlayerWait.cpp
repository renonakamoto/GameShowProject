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
	// �ړ����Ă����瑖�郂�[�V�����ɑJ��
	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSprint::GetInstance());
	}

	// C�������ꂽ�炽�炵�Ⴊ�ރ��[�V�����ɑJ��
	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSquat::GetInstance());
	}

	
	player_->Motion(PlayerMotionList::Wait);
}