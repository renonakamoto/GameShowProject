#include "Tent.h"
#include "../../../Collision/Shape/Cylinder.h"

Tent::Tent(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
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