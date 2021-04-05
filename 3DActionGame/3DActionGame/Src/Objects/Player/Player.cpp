#include "Player.h"
#include "../../Engine/InputManager.h"
#include "../../Utility/Calculation.h"
#include "PlayerMotion/IdleState.h"
#include "../../ObjectManager/ObjectManager.h"

void Player::Init()
{
	m_Scale.x = 0.1f;
	m_Scale.y = 0.1f;
	m_Scale.z = 0.1f;

	m_Model = FbxStorage::GetInstance()->GetModel("Ekard");
	m_State = IdleState::GetInstance();
	m_State->Enter(this);

	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		float y = m_Stage->GetPolygonHeight(m_Pos);
		m_Pos.y = y;
	}
	
	ObjectBase* camera = ObjectManager::GetInstance()->GetObj("FollowCamera");
	if (camera) m_Camera = dynamic_cast<FollowCamera*>(camera);
	if (m_Camera)
	{
		m_Camera->SetFollowObject(this);
		m_Camera->SetDistance(27.0f);
		m_Camera->SetOffset(DirectX::XMFLOAT3(0.0f, 9.f, 0.0f));
	}

}

void Player::Update()
{
#ifdef _DEBUG
	
	static DirectX::XMFLOAT3 offset(0.0f, 9.f, 0.0f);

	if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_T))
	{
		offset.y++;
		m_Camera->SetOffset(offset);
	}

	if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_G))
	{
		offset.y--;
		m_Camera->SetOffset(offset);
	}

#endif
	

	// プレイヤーの状態を更新する
	PlayerState* state = m_State->CheckState(this);

	// 前のフレームの状態と違った場合は更新する
	if (state != m_State)
	{
		m_State = state;
		m_State->Enter(this);
	}

	// 
	m_State->Update(this);
	
	// モーションのフレームを進める
	m_Model->Animate();
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
	
}

void Player::Move(float x_, float z_)
{
	if (x_ == 0.f && z_ == 0.f) {
		m_IsMove = false;
		return;
	}
	m_IsMove = true;

	m_OldPos = m_Pos;
	
	// 移動ベクトルを正規化
	DirectX::XMFLOAT2 normalized_move_vec = Calculation::Normalize(DirectX::XMFLOAT2(x_, z_));
	
	m_Pos.x +=  normalized_move_vec.x;
	m_Pos.z +=  normalized_move_vec.y;

	m_Angle = atan2f(normalized_move_vec.x, normalized_move_vec.y);
	m_Rot.y = DirectX::XMConvertToDegrees(m_Angle);

	float y = m_Stage->GetPolygonHeight(m_Pos);
	m_Pos.y = y;
}