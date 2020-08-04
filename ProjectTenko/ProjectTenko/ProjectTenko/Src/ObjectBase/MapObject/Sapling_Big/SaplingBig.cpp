#include "SaplingBig.h"
#include "../../../Collision/Shape/AABB.h"
#include "../../../Utility/SimpleCalculation.h"

SaplingBig::SaplingBig(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_):
	MapObject(mapObjcectList_, key_)
{	
	m_Width  = 100.0f;
	m_Height = 100.0f;
	m_Depth  = 50.0f;


	D3DXVECTOR3 scale;	// x = width // y = height // z = depth
	int shape_num = 0;
	for (const auto& itr : *m_MapObjectDataList)
	{
		scale.x = m_Width  * itr.m_Scale.x;
		scale.y = m_Height * itr.m_Scale.y;
		scale.z = m_Depth  * itr.m_Scale.z;

		SimpleCalculation::D3DXVec3RotationX(&scale, itr.m_Rot.x);
		SimpleCalculation::D3DXVec3RotationY(&scale, itr.m_Rot.y);
		SimpleCalculation::D3DXVec3RotationZ(&scale, itr.m_Rot.z);

		m_Shape.push_back(new AABBShape(scale.x, scale.y, scale.z));
		m_Shape[shape_num]->Update(itr.m_Pos);
		shape_num++;
	}

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

void SaplingBig::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Sapling_Big);
#endif
	for (const auto& itr : *m_MapObjectDataList)
	{
		int shape_num = 0;
		m_Shape[shape_num]->Update(itr.m_Pos);
		shape_num++;
	}
}

void SaplingBig::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}
