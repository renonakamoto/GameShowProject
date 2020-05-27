#include "Floor.h"

Floor::Floor(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
	MapObject(pos_, key_, mapObjcectList_)
{
}

void Floor::Update()
{
}

void Floor::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
