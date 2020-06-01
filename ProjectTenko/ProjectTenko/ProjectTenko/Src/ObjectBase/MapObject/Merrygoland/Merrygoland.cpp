#include "Merrygoland.h"

Merrygoland::Merrygoland(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
{
	//THE_FBXMANAGER->LoadFBXMesh(m_FbxKey, "assets/objects/merrygoland/merrygoland_Foundation.fbx");
	//THE_FBXMANAGER->LoadFBXMesh("merrygoland_Paul",    "assets/objects/merrygoland/merrygoland_Paul.fbx");
	//THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp1", "assets/objects/merrygoland/merrygoland_shrimp1.fbx");
	//THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp2", "assets/objects/merrygoland/merrygoland_shrimp2.fbx");
	//THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp3", "assets/objects/merrygoland/merrygoland_shrimp3.fbx");
	//THE_FBXMANAGER->LoadFBXMesh("merrygoland_shrimp4", "assets/objects/merrygoland/merrygoland_shrimp4.fbx");

}

void Merrygoland::Update()
{
	CoordinateUpdate(MapData::Merrygoland);
}

void Merrygoland::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMATRIX mat_scale;
	D3DXMATRIX mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;

	for (const auto& itr : m_MapObjectDataList)
	{
		D3DXMatrixTranslation(&mat_trans, itr.m_Pos.x, itr.m_Pos.y, itr.m_Pos.z);
		D3DXMatrixScaling(&mat_scale, itr.m_Scale.x, itr.m_Scale.y, itr.m_Scale.z);
		D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(itr.m_Rot.x));
		D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(itr.m_Rot.y));
		D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(itr.m_Rot.z));
		mat_rot = mat_rot_x * mat_rot_y * mat_rot_z;

		m_Mat_World = mat_scale * mat_rot * mat_trans;
		THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
	}
}
