#include "EnemyDeathState.h"
#include "../Enemy.h"

EnemyState* EnemyDeathState::CheckState(Enemy* enemy_)
{
	return EnemyDeathState::GetInstance();
}

void EnemyDeathState::Update(Enemy* enemy_)
{
	SkeletalModel* model = enemy_->m_Model;

	if (model->GetCurrentFrame() >= model->GetModel()->GetMotionData("Death")->FrameNum - 2) {
		enemy_->m_IsDeath = true;
	}
}

void EnemyDeathState::Enter(Enemy* enemy_)
{
	enemy_->m_Model->Play("Death");
}
