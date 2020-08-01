#ifndef MERRYGOLAND_H_
#define MERRYGOLAND_H_

#include "../MapObject.h"
#include "../../../Collision/Shape/Cylinder.h"
#include "../../../Utility/SimpleCalculation.h"

/**
* @brief メリーゴーランドクラス
*/
class Merrygoland : public MapObject
{
	enum class MerrygolandParts
	{
		Merrygoland_Foundation,
		Merrygoland_Paul,
		Merrygoland_Shrimp1,
		Merrygoland_Shrimp2,
		Merrygoland_Shrimp3,
		Merrygoland_Shrimp4
	};

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

private:
	std::vector<D3DXMATRIX> m_WorldShrimpParts;	//! 海老の部分(回すところ)のワールド行列

};

template<typename ...KeyList>
inline Merrygoland::Merrygoland(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList_):
	MapObject(mapObjcectList_, keyList_...)
{
	D3DXVECTOR3 scale;
	int shape_num = 0;
	for (const auto& itr : *m_MapObjectDataList)
	{
		scale.x = m_Width  * itr.m_Scale.x;
		scale.y = m_Height * itr.m_Scale.y;
		scale.z = m_Depth  * itr.m_Scale.z;

		SimpleCalculation::D3DXVec3RotationX(&scale, itr.m_Rot.x);
		SimpleCalculation::D3DXVec3RotationY(&scale, itr.m_Rot.y);
		SimpleCalculation::D3DXVec3RotationZ(&scale, itr.m_Rot.z);

		m_Shape.push_back(new CylinderShape(130.0f, 180.0f));
		m_Shape[shape_num]->Update(itr.m_Pos);
		shape_num++;
	}

	D3DXMATRIX mat_world;
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
		mat_world = mat_scale * mat_rot * mat_trans;

		m_WorldShrimpParts.push_back(mat_world);
		m_MatWorld.push_back(mat_world);
	}
}

#endif