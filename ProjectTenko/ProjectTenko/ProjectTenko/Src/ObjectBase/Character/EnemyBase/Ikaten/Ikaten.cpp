#include "Ikaten.h"

Ikaten::Ikaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_AttackRange(5.0f)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/ikaten/.fbx");
}

void Ikaten::Update()
{
}

void Ikaten::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}

void Ikaten::Patrol()
{
}

void Ikaten::Turn()
{
}

void Ikaten::Chase()
{
}

void Ikaten::Return()
{
}

void Ikaten::Thinking()
{
}

void Ikaten::Attack()
{
	
}

bool Ikaten::IsPlayerRanged()
{
	return false;
}
