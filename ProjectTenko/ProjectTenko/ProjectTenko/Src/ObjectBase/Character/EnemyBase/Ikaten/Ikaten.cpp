#include "Ikaten.h"

Ikaten::Ikaten(D3DXVECTOR3 pos_, std::string key_) :
	Enemybase(pos_, key_)
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
