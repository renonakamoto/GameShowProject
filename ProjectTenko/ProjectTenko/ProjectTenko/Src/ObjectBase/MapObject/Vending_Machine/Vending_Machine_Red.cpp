#include "Vending_Machine_Red.h"
#include "../../../Collision/Shape/AABB.h"

VendingMachineRed::VendingMachineRed(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
{
	m_Shape = new AABBShape(20.f, 40.f, 15.f);
	m_Shape->Update(m_Pos);
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
