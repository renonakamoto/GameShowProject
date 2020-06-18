#include "Sitaketen.h"

Sitaketen::Sitaketen(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/sitaketen/.fbx");
}

void Sitaketen::Update()
{
}

void Sitaketen::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
