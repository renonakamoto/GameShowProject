#include "../Player.h"
#include "PlayerAttack02State.h"
#include "PlayerIdleState.h"

PlayerState* PlayerAttack02State::CheckState(Player* player_)
{
	if (player_->m_IsHit)
	{
		return PlayerHitState::GetInstance();
	}

	UINT current_frame = player_->m_Model->GetCurrentFrame();
	UINT attack_frame  = player_->m_Model->GetModel()->GetMotionData("Attack02")->FrameNum;

	// 攻撃モーションが終了したら待機状態へ遷移
	if (current_frame >= attack_frame - 1) {
		return PlayerIdleState::GetInstance();
	}

	// 攻撃状態
	return PlayerAttack02State::GetInstance();
}

void PlayerAttack02State::Update(Player* player_)
{
	// 攻撃を与えるフレームにきたら攻撃を行う
	if (player_->m_Model->GetCurrentFrame() == m_AttackFrame) {
		player_->Attack();
	}
}

void PlayerAttack02State::Enter(Player* player_)
{
	player_->SetMotion("Attack02");
}
