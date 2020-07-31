#ifndef MERRYGOLAND_H_
#define MERRYGOLAND_H_

#include "../MapObject.h"
#include "../../../Collision/Shape/Cylinder.h"

/**
* @brief メリーゴーランドクラス
*/
class Merrygoland : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	template<typename... KeyList>
	Merrygoland(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Merrygoland() {}

	/**
	* @brief 更新関数
	*/
	virtual void Update() override;

	/**
	* @brief 描画関数
	*/
	virtual void Draw() override;


};

template<typename ...KeyList>
inline Merrygoland::Merrygoland(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList_):
	MapObject(mapObjcectList_, keyList_...)
{
	m_Shape.push_back(new CylinderShape(130.0f, 180.0f));
	m_Shape[0]->Update(m_MapObjectDataList[0][0].m_Pos);

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

#endif