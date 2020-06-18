#include "Vending_Machine_Blue.h"
#include "../../../Collision/Shape/AABB.h"

VendingMachineBlue::VendingMachineBlue(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
{
	int shape_num = 0;
	for (const auto& itr : m_MapObjectDataList)
	{
		m_Shape.push_back(new AABBShape(itr.m_Width, itr.m_Height, itr.m_Depth));
		m_Shape[shape_num]->Update(itr.m_Pos);
		shape_num++;
	}
}

void VendingMachineBlue::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Vending_Machine);
}

void VendingMachineBlue::Draw()
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
