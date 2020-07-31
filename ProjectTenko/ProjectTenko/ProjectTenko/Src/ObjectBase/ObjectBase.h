#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_

#include "../Engine/Fbx/FbxManager.h"
#include "../Collision/Shape/Shape.h"
#include <d3dx9.h>
#include <string>
#include <vector>

/**
* @brief �I�u�W�F�N�g���N���X
*/
class ObjectBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ObjectBase() :
		m_Pos   (D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Angle (0.f),
		m_Width (0.f),
		m_Height(0.f),
		m_Depth (0.f)
	{}

	/**
	* @brief �R���X�g���N�^
	*/
	ObjectBase(D3DXVECTOR3 pos_) :
		m_Pos(pos_),
		m_Angle(0.f),
		m_Width(0.f),
		m_Height(0.f),
		m_Depth(0.f)
	{}

	/**
	* @brief �R���X�g���N�^
	*/
	ObjectBase(D3DXVECTOR3 pos_, float width_, float height_, float depth_) :
		m_Pos   (pos_),
		m_Width (width_),
		m_Height(height_),
		m_Depth (depth_),
		m_Angle (0.0f)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~ObjectBase() 
	{
		for(size_t i = 0; i < m_Shape.size(); i++)
		{ 
			delete m_Shape[i];
		}

		m_Shape.clear();
	}

	/**
	* @brief �X�V�֐�
	*/
	virtual void Update() {}

	/**
	* @brief �`��֐�
	*/
	virtual void Draw() {}

	/**
	* @brief ���W��Ԃ��֐�
	*/
	D3DXVECTOR3 GetPos() const{ return m_Pos; }

	/**
	* @brief �����蔻��̌`���Ԃ��֐�
	*/
	std::vector<Shape*> GetShape() const{ return m_Shape; }

	/**
	* @brief �p�x��Ԃ��֐�
	*/
	float GetAngle() const{ return m_Angle; }

protected:

	//! ���W
	D3DXVECTOR3 m_Pos;

	//! �p�x
	float		m_Angle;

	//! ����
	float		m_Width;

	//! ����
	float		m_Height;

	//! ���s��
	float		m_Depth;

	//! �`��N���X
	std::vector<Shape*> m_Shape;

};

#endif