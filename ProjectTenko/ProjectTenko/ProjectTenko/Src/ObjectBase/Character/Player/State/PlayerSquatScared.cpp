#include "PlayerSquatScared.h"
#include "../Player.h"
#include "PlayerScared.h"

void PlayerSquatScared::Init(Player* player_)
{
	m_FinishedMotionion = false;
}

void PlayerSquatScared::Update(Player* player_)
{
	// 怯えてしゃがむモーションが終わったら「怯える」に遷移
	if (m_FinishedMotionion)
	{
		player_->ChangeState(PlayerScared::GetInstance());
	}

	player_->Motion(PlayerMotionList::Squat_Scared, false, &m_FinishedMotionion);
}
