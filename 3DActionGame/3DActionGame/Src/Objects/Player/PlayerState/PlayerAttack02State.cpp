#include "../Player.h"
#include "PlayerAttack02State.h"
#include "PlayerIdleState.h"

PlayerState* PlayerAttack02State::CheckState(Player* player_)
{
	UINT current_frame = player_->m_Model->GetCurrentFrame();
	UINT attack_frame  = player_->m_Model->GetModel()->GetMotionData("Attack02")->FrameNum;

	if (current_frame >= attack_frame - 1) {
		return PlayerIdleState::GetInstance();
	}
	
	return PlayerAttack02State::GetInstance();
}

void PlayerAttack02State::Update(Player* player_)
{
	if (player_->m_Model->GetCurrentFrame() == m_AttackFrame) {
		player_->Attack();
	}
}

void PlayerAttack02State::Enter(Player* player_)
{
	player_->SetMotion("Attack02");
}
