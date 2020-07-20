#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Shape.h"
#include <d3dx9.h>

/**
* @brief �~���N���X
*/
class CylinderShape : public Shape
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	CylinderShape(float radius_, float height_):
		m_Radius(radius_),
		m_Height(height_),
		m_CenterPos(D3DXVECTOR3())
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~CylinderShape() {}

	/**
	* @brief �R���W�����X�V�֐�
	* @details �I�u�W�F�N�g�̍��W���ς�������ɓ����蔻��p�I�u�W�F�N�g�̍��W���ύX����
	* @param[in] pos_ �I�u�W�F�N�g�̍��W
	*/
	void Update(const D3DXVECTOR3& pos_) override {
		m_CenterPos = pos_;
	}

	/**
	* @brief ���g�̌`���Ԃ��֐�
	* @return SHAPE_TYPE
	*/
	SHAPE_TYPE GetType() const       override { return SHAPE_TYPE::Shape_Cylinder; }

	/**
	* @brief ���g�̍��W��Ԃ��֐�
	* @return SHAPE_TYPE
	*/
	D3DXVECTOR3 GetPos() const override { return m_CenterPos; }

	/**
	* @brief ���a��Ԃ��֐�
	* @return float 
	*/
	float GetRadius() const			 override { return m_Radius; }

	/**
	* @brief ������Ԃ��֐�
	* @return float
	*/
	float GetHeight() const			 override { return m_Height; }

private:
	D3DXVECTOR3 m_CenterPos;	//! ���S�_
	float       m_Radius;		//! ���a
	float       m_Height;		//! ����

};

#endif