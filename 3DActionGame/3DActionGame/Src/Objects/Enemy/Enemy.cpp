#include "Enemy.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../CollisionManager/Shape/3D/OBB/ShapeOBB.h"
#include "../../Engine/Engine.h"

void Enemy::Update()
{
	// 状態のチェックを行う
	EnemyState* state = m_State->CheckState(this);

	// 前のフレームの状態と違った場合は更新する
	if (state != m_State)
	{
		m_State = state;
		m_State->Enter(this);
	}
	
	// ステートの更新
	m_State->Update(this);
	
	// モーションのフレームを進める
	m_Model->Animate();
}

void Enemy::Draw()
{
	GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	if (m_Model)m_Model->Render( m_Pos, m_Scale, m_Rot);
}

void Enemy::Damage(int damageNum_)
{
	m_Hp -= damageNum_;

	m_IsHit = true;
}

void Enemy::Init()
{
	// モデル情報の取得
	m_Model = new SkeletalModel(FbxStorage::GetInstance()->GetModel("Enemy"));
	
	// ステートの初期化
	m_State = EnemyIdleState::GetInstance();
	m_State->Enter(this);

	// 参照用のステージを取得
	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("Stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
	}

	// 当たり判定用OBBの初期化
	DirectX::XMFLOAT3 shape_pos = m_Pos;
	shape_pos.y = m_Pos.y + m_EnemySize.y / 2;
	m_Shape = new ShapeOBB(shape_pos, m_EnemySize.x / 2, m_EnemySize.y / 2, m_EnemySize.z / 2);
	
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->Register(this);
}

void Enemy::Release()
{
	CollisionManager::GetInstance()->Release(this);	
	delete m_Model;
	m_Model = nullptr;
}