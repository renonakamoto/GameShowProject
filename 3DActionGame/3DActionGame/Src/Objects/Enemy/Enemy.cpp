#include "Enemy.h"
#include "../../ObjectManager/ObjectManager.h"

void Enemy::Update()
{

	
	// モーションのフレームを進める
	m_Model->Animate();
}

void Enemy::Draw()
{
	DirectGraphics::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	if (m_Model)m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Pos);
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
	
}

void Enemy::Release()
{
}