#include "Player.h"

void Player::Init()
{
	m_Model = FbxStorage::GetInstance()->GetModel("Ekard");
	m_Model->Play("Run");
}

void Player::Update()
{
	m_Model->Animate();
}

void Player::Draw()
{
	m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Rot);
}

void Player::Release()
{
}
