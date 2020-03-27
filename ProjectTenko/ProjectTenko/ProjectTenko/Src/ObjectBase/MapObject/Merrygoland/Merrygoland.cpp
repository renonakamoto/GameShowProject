#include "Merrygoland.h"

Merrygoland::Merrygoland(D3DXVECTOR3 pos_, std::string key_) :
	MapObject(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/merrygoland/marry03.fbx");
	THE_FBXMANAGER->LoadFBXMesh("merrygoland_Paul",    "assets/objects/merrygoland/marry03.fbx");
	THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp1", "assets/objects/merrygoland/marry03.fbx");
	THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp2", "assets/objects/merrygoland/marry03.fbx");
	THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp3", "assets/objects/merrygoland/marry03.fbx");
	THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp4", "assets/objects/merrygoland/marry03.fbx");

}

void Merrygoland::Update()
{
}

void Merrygoland::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
