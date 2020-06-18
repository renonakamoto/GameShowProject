#include "Vending_Machine_Red.h"
#include "../../../Collision/Shape/AABB.h"

VendingMachineRed::VendingMachineRed(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
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

void VendingMachineRed::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Vending_Machine);
}

void VendingMachineRed::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
