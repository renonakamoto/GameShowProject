#ifndef RAY_H_
#define RAY_H_

#include "Shape.h"
#include <d3dx9.h>

/**
* @brief ���C�N���X
*/
class Ray : public Shape
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Ray():
		m_Origin(D3DXVECTOR3()),
		m_Delta(D3DXVECTOR3())
	{}

	/**
	* @brief �R���X�g���N�^
	*/
	Ray(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_):
		m_Origin(origin_),
		m_Delta(delta_)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~Ray(){}

	/**
	* @brief ��֐�
	*/
	virtual void Update(const D3DXVECTOR3& pos_) override {}

	/**
	* @brief ���C�̏����Z�b�g����֐�
	* @param[in] origin_ �����̌��_
	* @param[in] delta_  �����̒����ƌ���
	*/
	void SetRay(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_) override
	{
		m_Origin = origin_;
		m_Delta  = delta_;
	}

	/**
	* @brief ���g�̌`���Ԃ��֐�
	* @return SHAPE_TYPE
	*/
	virtual SHAPE_TYPE GetType() const override { return SHAPE_TYPE::Shape_Ray; }

	/**
	* @brief ���g�̍��W(���S�_)��Ԃ��֐�
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetPos() const override   { return m_Origin; }

	/**
	* @brief �����̌��_��Ԃ��֐�
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetOrigin()const  { return m_Origin; }

	/**
	* @brief �����̒����ƌ�����Ԃ��֐�
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetDelta()const   { return m_Delta;  }

private:
	D3DXVECTOR3 m_Origin;	//! �����̌��_
	D3DXVECTOR3 m_Delta;	//! �����̒����ƌ���
	
};

#endif