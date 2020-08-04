#ifndef FERRISWHEEL_H_
#define FERRISWHEEL_H_

#include "../MapObject.h"
#include "../../../Utility/SimpleCalculation.h"
#include "../../../Collision/Shape/AABB.h"

/**
* @brief �ϗ��ԃN���X
*/
class FerrisWheel : public MapObject
{
	enum class FerrisWheelParts
	{
		FerrisWheel_Foundation,
		FerrisWheel_Rotating,
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	template<typename... KeyList>
	FerrisWheel(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~FerrisWheel() {}

	/**
	* @brief �X�V�֐�
	*/
	virtual void Update() override;

	/**
	* @brief �`��֐�
	*/
	virtual void Draw() override;

private:
	std::vector<D3DXMATRIX> m_WorldRotatingParts;	//! �ϗ��Ԃ̉�镔���̃��[���h�s��

};

template<typename ...KeyList>
inline FerrisWheel::FerrisWheel(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList_):
	MapObject(mapObjcectList_, keyList_...)
{
	int shape_num = 0;
	for (const auto& itr : *m_MapObjectDataList)
	{
		m_Shape.push_back(new AABBShape(340.0f, 340.0f, 210.0f));
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

		m_WorldRotatingParts.push_back(mat_world);
		m_MatWorld.push_back(mat_world);
	}
}

#endif