#include "EnemyHitState.h"
#include "../Enemy.h"

EnemyState* EnemyHitState::CheckState(Enemy* enemy_)
{
	if (enemy_->m_Hp < 0)
	{
		return EnemyDeathState::GetInstance();
	}

	if (enemy_->m_IsHit == true)
	{
		enemy_->m_IsHit = false;
		enemy_->m_Model->SetFrame(0.f);
	}

	if (enemy_->m_Model->GetCurrentFrame() >= 29.f) {
		return EnemyIdleState::GetInstance();
	}

	return EnemyHitState::GetInstance();
}

void EnemyHitState::Update(Enemy* enemy_)
{
}

void EnemyHitState::Enter(Enemy* enemy_)
{
	enemy_->m_Model->Play("Hit");
}
