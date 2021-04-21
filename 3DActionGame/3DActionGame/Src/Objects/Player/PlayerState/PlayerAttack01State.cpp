#include "../Player.h"
#include "PlayerAttack01State.h"
#include "PlayerAttack02State.h"
#include "PlayerIdleState.h"
#include "../../../Engine/Engine.h"

PlayerState* PlayerAttack01State::CheckState(Player* player_)
{
	UINT current_frame = player_->m_Model->GetCurrentFrame();
	UINT attack_frame  = player_->m_Model->GetModel()->GetMotionData("Attack01")->FrameNum;

	// 攻撃モーションが終了したら待機状態へ遷移
	if (current_frame >= attack_frame - 1) {
		return PlayerIdleState::GetInstance();
	}
	
	// 連続攻撃が可能なフレーム　かつ　左クリックが押された時次の攻撃状態へ遷移
	if (player_->m_Model->GetCurrentFrame() >= m_AttackChainFrame && INPUT->GetMouseDown(MouseButton::Left))
	{
		return PlayerAttack02State::GetInstance();
	}

	// 攻撃状態
	return PlayerAttack01State::GetInstance();
}

void PlayerAttack01State::Update(Player* player_)
{
	// 攻撃を与えるフレームにきたら攻撃を行う
	if (player_->m_Model->GetCurrentFrame() == m_AttackFrame) {
		player_->Attack();
	}
}

void PlayerAttack01State::Enter(Player* player_)
{
	player_->SetMotion("Attack01");
}
