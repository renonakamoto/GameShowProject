#ifndef SHAPE_H_
#define SHAPE_H_

#include <d3dx9.h>

enum class SHAPE_TYPE
{
	Shape_AABB,
	Shape_Cylinder,
	Shape_Ray,

	Shape_Type_Num,
};

/**
* @brief �����蔻��Ɏg���`�̊��N���X
*/
class Shape
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Shape() {}

	/**
	* @brief �R���W�����X�V�֐�
	* @details �I�u�W�F�N�g�̍��W���ς�������ɓ����蔻��p�I�u�W�F�N�g�̍��W���ύX����
	* @param[in] pos_ �I�u�W�F�N�g�̍��W
	*/
	virtual void Update(const D3DXVECTOR3& pos_) = 0;

	/**
	* @brief �`��Ԃ��֐�
	*/
	virtual SHAPE_TYPE GetType() const = 0;

	/**
	* @brief ����p�I�u�W�F�N�g�̍��W��Ԃ�
	*/
	virtual D3DXVECTOR3 GetPos()const = 0;

public:

	virtual D3DXVECTOR3 GetMin() const { return D3DXVECTOR3(); }
	virtual D3DXVECTOR3 GetMax() const { return D3DXVECTOR3(); }

public:
	
	virtual D3DXVECTOR3 GetCenterPos() const { return D3DXVECTOR3(); }
	virtual float GetRadius() const { return 0.f; }
	virtual float GetHeight() const { return 0.f; }
	virtual void  SetRay(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_){}

public:
	virtual D3DXVECTOR3 GetOrigin()const { return D3DXVECTOR3(); }
	virtual D3DXVECTOR3 GetDelta()const  { return D3DXVECTOR3(); }
};

#endif