#include "PlayerHitState.h"
#include "../Player.h"
#include "PlayerIdleState.h"

PlayerState* PlayerHitState::CheckState(Player* player_)
{
	UINT current_frame = player_->m_Model->GetCurrentFrame();
	UINT motion_frame  = player_->m_Model->GetModel()->GetMotionData("Stun")->FrameNum;

	if (player_->m_Hp <= 0)
	{
		if (current_frame >= motion_frame - 1) {
			player_->m_IsDeath = true;
			return PlayerIdleState::GetInstance();
		}
	}
	else
	{
		if (current_frame >= motion_frame / 3) {
			return PlayerIdleState::GetInstance();
		}
	}
	
	return PlayerHitState::GetInstance();
}

void PlayerHitState::Update(Player* player_)
{
}

void PlayerHitState::Enter(Player* player_)
{
	player_->m_IsHit = false;
	player_->SetMotion("Stun");
}