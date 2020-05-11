#include "Wall.h"
#include "../../../Collision/Shape/AABB.h"

Wall::Wall(D3DXVECTOR3 pos_, std::string key_) :
	MapObject(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/wall/wall.fbx");

	m_Shape = new AABBShape(3.0f, 25.0f, 40.0f);
	m_Shape->Update(m_Pos);
}

void Wall::Update()
{
}

void Wall::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
