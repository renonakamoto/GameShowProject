#include "Player.h"
#include "../../Engine/InputManager.h"
#include "../../Utility/Calculation.h"

void Player::Init()
{
	m_Model = FbxStorage::GetInstance()->GetModel("Ekard");
	m_Model->Play("Run");
}

void Player::Update()
{
	// 移動ベクトル
	DirectX::XMFLOAT2 move_vec(0.f, 0.f);
	// 左
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_A)) move_vec.x = -m_Speed;
	// 右
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_D)) move_vec.x = m_Speed;
	// 前
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_W)) move_vec.y = m_Speed;
	// 後
	if (InputManager::GetInstance()->GetKey(KeyInfo::Key_S)) move_vec.y = -m_Speed;

	Move(move_vec.x, move_vec.y);

	if (!m_Attacking && InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		m_Attacking = true;
	}
	if (m_Attacking || m_Attacking2)
	{
		Attack();
	}

	UpdateMotion();
}

void Player::Draw()
{
	m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Rot);
}

void Player::Release()
{
}

void Player::Attack()
{
	m_AttackFlameCount++;

	if (m_AttackFlameCount > 40 && InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		m_Attacking  = false;
		m_Attacking2 = true;
		m_AttackFlameCount = 0;
	}

	if (m_AttackFlameCount > 64)
	{
		m_Attacking2 = false;
		m_Attacking = false;
		m_AttackFlameCount = 0;
	}
}

void Player::Move(float x_, float z_)
{
	if (m_Attacking)return;
	if (x_ == 0.f && z_ == 0.f) {
		m_IsMove = false;
		return;
	}
	m_IsMove = true;

	m_OldPos = m_Pos;
	
	// 移動ベクトルを正規化
	DirectX::XMFLOAT2 normalized_move_vec = Calculation::Normalize(DirectX::XMFLOAT2(x_, z_));
	
	m_Pos.x += normalized_move_vec.x;
	m_Pos.z += normalized_move_vec.y;

	m_Angle = atan2f(normalized_move_vec.x, normalized_move_vec.y);
	m_Rot.y = DirectX::XMConvertToDegrees(m_Angle);
}

void Player::UpdateMotion()
{

	if (m_Attacking == true)
	{
		m_Model->Play("Atack1");
	}
	else if (m_Attacking2)
	{
		m_Model->Play("Atack2");
	}
	else if (m_IsMove == true)
	{
		m_Model->Play("Run");
	}
	else
	{
		m_Model->Play("Idle");
	}

	m_Model->Animate();
}
