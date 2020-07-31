#include "Gate.h"
#include "../../../Collision/Shape/Cylinder.h"

Gate::Gate(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_) :
	MapObject(mapObjcectList_, key_)
{
	// -714 0 43	//40
	// -714 0 107	//32
	// -714 0 156	//21
	
	// -714 0 -83	//40 
	// -714 0 -143	//32
	// -714 0 -187	//21
	// -714 0 -219	//15

	m_Shape.push_back(new CylinderShape(20.0f, 180.0f));
	m_Shape[0]->Update(D3DXVECTOR3(-714.0f, 0.0f, 43.0f));

	m_Shape.push_back(new CylinderShape(16.0f, 180.0f));
	m_Shape[1]->Update(D3DXVECTOR3(-714.0f, 0.0f, 107.0f));

	m_Shape.push_back(new CylinderShape(10.5f, 180.0f));
	m_Shape[2]->Update(D3DXVECTOR3(-714.0f, 0.0f, 156.0f));

	m_Shape.push_back(new CylinderShape(20.0f, 180.0f));
	m_Shape[3]->Update(D3DXVECTOR3(-714.0f, 0.0f, -83.0f));

	m_Shape.push_back(new CylinderShape(16.0f, 180.0f));
	m_Shape[4]->Update(D3DXVECTOR3(-714.0f, 0.0f, -143.0f));

	m_Shape.push_back(new CylinderShape(10.5f, 180.0f));
	m_Shape[5]->Update(D3DXVECTOR3(-714.0f, 0.0f, -187.0f));

	m_Shape.push_back(new CylinderShape(7.5f, 180.0f));
	m_Shape[6]->Update(D3DXVECTOR3(-714.0f, 0.0f, -219.0f));


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


void Gate::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Gate);
}

void Gate::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}