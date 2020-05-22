#include "Skydome.h"

Skydome::Skydome(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
{
	THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/skydome/sky_dome4.fbx");
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}