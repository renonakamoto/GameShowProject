#include "EnemyDeathState.h"
#include "../Enemy.h"

EnemyState* EnemyDeathState::CheckState(Enemy* enemy_)
{
	return EnemyDeathState::GetInstance();
}

void EnemyDeathState::Update(Enemy* enemy_)
{
	SkeletalModel* model = enemy_->m_Model.get();

	// 死亡モーションが終了したら死亡フラグをtrueにする
	if (model->GetCurrentFrame() >= model->GetModel()->GetMotionData("Death")->FrameNum - 2) {
		enemy_->m_IsDeath = true;
	}
}

void EnemyDeathState::Enter(Enemy* enemy_)
{
	// 死亡モーションを再生する
	enemy_->m_Model->Play("Death");
}
