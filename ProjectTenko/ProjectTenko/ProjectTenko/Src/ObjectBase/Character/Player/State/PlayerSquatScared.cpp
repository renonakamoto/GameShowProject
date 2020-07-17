#include "PlayerSquatScared.h"
#include "../Player.h"
#include "PlayerScared.h"

void PlayerSquatScared::Init(Player* player_)
{
	m_FinishedMotionion = false;
}

void PlayerSquatScared::Update(Player* player_)
{
	// �����Ă��Ⴊ�ރ��[�V�������I�������u������v�ɑJ��
	if (m_FinishedMotionion)
	{
		player_->ChangeState(PlayerScared::GetInstance());
	}

	player_->Motion(PlayerMotionList::Squat_Scared, false, &m_FinishedMotionion);
}
