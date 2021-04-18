#include "EnemyHitState.h"
#include "../Enemy.h"

EnemyState* EnemyHitState::CheckState(Enemy* enemy_)
{
	// HPが0以下になったら死亡状態に遷移
	if (enemy_->m_Hp <= 0)
	{
		return EnemyDeathState::GetInstance();
	}
	
	// ヒットモーション中に攻撃をくらったら、フレームを0に戻す
	if (enemy_->m_IsHit == true)
	{
		enemy_->m_IsHit = false;
		enemy_->m_Model->SetFrame(0.f);
	}
	
	// ヒットモーションが終了したら待機状態に遷移
	if (enemy_->m_Model->GetCurrentFrame() >= HitMotionFrameNum) {
		return EnemyIdleState::GetInstance();
	}

	return EnemyHitState::GetInstance();
}

void EnemyHitState::Update(Enemy* enemy_)
{
}

void EnemyHitState::Enter(Enemy* enemy_)
{
	// ヒットモーションを再生する
	enemy_->m_Model->Play("Hit");
}
