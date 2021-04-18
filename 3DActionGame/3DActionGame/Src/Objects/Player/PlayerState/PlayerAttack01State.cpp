#include "../Player.h"
#include "PlayerAttack01State.h"
#include "PlayerAttack02State.h"
#include "PlayerIdleState.h"
#include "../../../Engine/InputManager.h"

PlayerState* PlayerAttack01State::CheckState(Player* player_)
{
	UINT current_frame = player_->m_Model->GetCurrentFrame();
	UINT attack_frame  = player_->m_Model->GetModel()->GetMotionData("Attack01")->FrameNum;

	if (current_frame >= attack_frame - 1) {
		return PlayerIdleState::GetInstance();
	}

	if (player_->m_Model->GetCurrentFrame() >= 40 && InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		return PlayerAttack02State::GetInstance();
	}

	return PlayerAttack01State::GetInstance();
}

void PlayerAttack01State::Update(Player* player_)
{
	if (player_->m_Model->GetCurrentFrame() == m_AttackFrame) {
		player_->Attack();
	}
}

void PlayerAttack01State::Enter(Player* player_)
{
	player_->SetMotion("Attack01");
}
