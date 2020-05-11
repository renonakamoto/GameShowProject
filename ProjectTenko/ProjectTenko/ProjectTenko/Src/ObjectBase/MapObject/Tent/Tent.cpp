#include "Tent.h"
#include "../../../Collision/Shape/Cylinder.h"

Tent::Tent(D3DXVECTOR3 pos_, std::string key_) :
	MapObject(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/tent/tent.fbx");
	m_Shape = new CylinderShape(160.f, 185.f);
	m_Shape->Update(m_Pos);
}

void Tent::Update()
{
}

void Tent::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}