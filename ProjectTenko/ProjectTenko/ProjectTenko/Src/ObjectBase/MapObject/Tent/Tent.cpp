#include "Tent.h"
#include "../../../Collision/Shape/Cylinder.h"

Tent::Tent(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_) :
	MapObject(mapObjcectList_, key_)
{
	m_Shape.push_back(new CylinderShape(160, 185.f));
	m_Shape[0]->Update((*m_MapObjectDataList)[0].m_Pos);

	D3DXMATRIX mat_trans;
	D3DXMATRIX mat_scale;
	D3DXMATRIX mat_rot, mat_rot_x, mat_rot_y, mat_rot_z;

	for (const auto& itr : *m_MapObjectDataList)
	{
		D3DXMatrixTranslation(&mat_trans, itr.m_Pos.x, itr.m_Pos.y, itr.m_Pos.z);
		D3DXMatrixScaling(&mat_scale, itr.m_Scale.x, itr.m_Scale.y, itr.m_Scale.z);
		D3DXMatrixRotationX(&mat_rot_x, D3DXToRadian(itr.m_Rot.x));
		D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(itr.m_Rot.y));
		D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(itr.m_Rot.z));
		mat_rot = mat_rot_x * mat_rot_y * mat_rot_z;

		m_MatWorld.push_back(mat_scale * mat_rot * mat_trans);
	}
}

void Tent::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Tent);
}

void Tent::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}