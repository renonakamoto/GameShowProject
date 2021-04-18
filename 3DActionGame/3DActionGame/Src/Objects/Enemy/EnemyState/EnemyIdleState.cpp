#include "EnemyIdleState.h"
#include "../Enemy.h"

EnemyState* EnemyIdleState::CheckState(Enemy* enemy_)
{
	// 攻撃をくらっていたらHitStateに状態を遷移
	if (enemy_->m_IsHit == true)
	{
		enemy_->m_IsHit = false;
		return EnemyHitState::GetInstance();
	}

	return EnemyIdleState::GetInstance();
}

void EnemyIdleState::Update(Enemy* enemy_)
{
}

void EnemyIdleState::Enter(Enemy* enemy_)
{
	// 待機モーションを再生する
	enemy_->m_Model->Play("Idle");
}
