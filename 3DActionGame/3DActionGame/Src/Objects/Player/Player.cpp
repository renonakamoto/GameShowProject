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
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
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

	m_AABB.m_Min.x = m_Pos.x - 1.3;
	m_AABB.m_Min.y = (m_Pos.y + 4) - 2;
	m_AABB.m_Min.z = m_Pos.z - 1;

	m_AABB.m_Max.x = m_Pos.x + 1.3;
	m_AABB.m_Max.y = (m_Pos.y + 4) + 2;
	m_AABB.m_Max.z = m_Pos.z + 1;

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
	DirectGraphics::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Rot);
	
	m_AABB.Draw();
}

void Player::Release()
{
}

void Player::Attack()
{
}

void Player::Move(float x_, float z_)
{
	m_OldPos = m_Pos;

	// 移動ベクトルを正規化
	m_Velocity = DirectX::XMFLOAT3(x_, 0.f, z_);
	if (m_Velocity.x != 0.f || m_Velocity.z != 0.f)
	{
		m_Velocity = Calculation::Normalize(m_Velocity);
	}
	
	m_Velocity = Calculation::Lerp(m_OldVelocity, m_Velocity, 5 * (1.0f / 60.0f));
	m_OldVelocity = m_Velocity;


	if (Calculation::Length(m_Velocity) > 0.2f)
	{
		float angle = atan2f(m_Velocity.x, m_Velocity.z);
		m_Rot.y = DirectX::XMConvertToDegrees(angle);

		m_Pos.x += m_Velocity.x;
		m_Pos.z += m_Velocity.z;
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
		
		// レイの原点
		//DirectX::XMFLOAT3 ray_origin = Calculation::Add(m_Pos, m_Velocity);
		//ray_origin.y = m_Pos.y + m_RayHeight;
		//
		//// レイの方向と長さ
		//DirectX::XMFLOAT3 ray_distance(0.0f, -30.0f, 0.0f);
		//
		//float height = 0.0f;
		//if (m_Stage->IntersectRayAndMap(ray_origin, ray_distance, height) == true) {
		//	m_Pos.x += m_Velocity.x;
		//	m_Pos.z += m_Velocity.z;
		//	m_Pos.y = height;
		//}
		
	}
}