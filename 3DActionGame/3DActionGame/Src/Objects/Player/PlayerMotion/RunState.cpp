#include "RunState.h"
#include "../Player.h"
#include "../../../Engine/InputManager.h"
#include "Attack01State.h"
#include "IdleState.h"

PlayerState* RunState::CheckState(Player* player_)
{
	if (InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		return Attack01State::GetInstance();
	}
	else if (InputManager::GetInstance()->GetKey(KeyInfo::Key_W) ||
			 InputManager::GetInstance()->GetKey(KeyInfo::Key_A) ||
			 InputManager::GetInstance()->GetKey(KeyInfo::Key_S) ||
			 InputManager::GetInstance()->GetKey(KeyInfo::Key_D))
	{
		return RunState::GetInstance();
	}

	return IdleState::GetInstance();
}

void RunState::Update(Player* player_)
{
	// 移動ベクトル
	DirectX::XMFLOAT2 move_vec(0.f, 0.f);
	// 左
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_A)) {
		move_vec.x -= player_->m_Camera->GetLeftNormal().x * player_->m_Speed;
		move_vec.y += player_->m_Camera->GetLeftNormal().z * player_->m_Speed;
	}
	// 右
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_D)) {
		move_vec.x += player_->m_Camera->GetLeftNormal().x * player_->m_Speed;
		move_vec.y -= player_->m_Camera->GetLeftNormal().z * player_->m_Speed;
	}
	// 前
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_W)) {
		move_vec.x += player_->m_Camera->GetFowardNormal().x * player_->m_Speed;
		move_vec.y += player_->m_Camera->GetFowardNormal().z * player_->m_Speed;
	}
	// 後
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_S)) {
		move_vec.x -= player_->m_Camera->GetFowardNormal().x * player_->m_Speed;
		move_vec.y -= player_->m_Camera->GetFowardNormal().z * player_->m_Speed;
	}

	player_->Move(move_vec.x, move_vec.y);
}

void RunState::Enter(Player* player_)
{
	player_->SetMotion("Run");
}