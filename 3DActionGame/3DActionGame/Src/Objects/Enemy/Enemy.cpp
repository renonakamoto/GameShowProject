#include "Enemy.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../Shape/3D/OBB/ShapeOBB.h"

void Enemy::Update()
{

	
	// モーションのフレームを進める
	m_Model->Animate();
}

void Enemy::Draw()
{
	DirectGraphics::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	if (m_Model)m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Rot);

	m_Shape->Draw();
}

void Enemy::Damage(int damageNum_)
{
	m_Hp -= damageNum_;

	if (m_Hp <= 0) {
		int hogev = 0;
	}
}

void Enemy::Init()
{
	m_Scale = DirectX::XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_Tag = "Enemy";

	m_Model = FbxStorage::GetInstance()->GetModel("Enemy");
	if (m_Model)m_Model->Play("Idle");

	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
	}

	DirectX::XMFLOAT3 shape_pos = m_Pos;
	shape_pos.y = m_Pos.y + 12.f;
	m_Shape = new ShapeOBB(shape_pos, 7.6f, 11.f, 6.8f);
	
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->Register(this);
}

void Enemy::Release()
{
}