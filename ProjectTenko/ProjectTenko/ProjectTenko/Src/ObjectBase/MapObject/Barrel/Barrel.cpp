#include "Barrel.h"
#include "../../../Collision/Shape/AABB.h"
#include "../../../Collision/Shape/Cylinder.h"

Barrel::Barrel(D3DXVECTOR3 pos_, std::string key_) :
	MapObject(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/barrel/Barrel.fbx");

	m_Shape = new AABBShape(20.f,150.f,20.f);

	m_Shape->Update(m_Pos);
}


void Barrel::Update()
{
}

void Barrel::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
