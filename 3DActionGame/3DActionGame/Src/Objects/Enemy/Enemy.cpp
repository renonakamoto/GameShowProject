#include "Enemy.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../CollisionManager/Shape/3D/OBB/ShapeOBB.h"
#include "../../Engine/Engine.h"

void Enemy::Update()
{
	if (m_IsDeath == true) {
		CollisionManager::GetInstance()->Release(this);
		ObjectManager::GetInstance()->Release(this);
		return;
	}

	// プレイヤーの状態を更新する
	EnemyState* state = m_State->CheckState(this);

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

void Enemy::Draw()
{
	GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	if (m_Model)m_Model->Render( m_Pos, m_Scale, m_Rot);

	m_Shape->Draw();
}

void Enemy::Damage(int damageNum_)
{
	m_Hp -= damageNum_;

	if (m_Hp <= 0) {
		int hogev = 0;
	}

	m_IsHit = true;
}

void Enemy::Init()
{
	m_Scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);

	m_Model = new SkeletalModel(); 
	m_Model->SetModel(FbxStorage::GetInstance()->GetModel("Enemy"));
	
	m_State = EnemyIdleState::GetInstance();
	m_State->Enter(this);

	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("Stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
	}

	DirectX::XMFLOAT3 shape_pos = m_Pos;
	shape_pos.y = m_Pos.y + 24.f;
	m_Shape = new ShapeOBB(shape_pos, 15.f, 20.f, 11.f);
	
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->Register(this);
}

void Enemy::Release()
{
	delete m_Model;
	m_Model = nullptr;
}