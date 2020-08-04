#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Collision/Shape/Shape.h"
#include "../Utility/Singleton.h"
#include <d3dx9.h>

class ObjectBase;

/**
* @brief �J�����N���X
* @details �ڍׂȃN���X�̐���
*/
class Camera //: public Singleton<Camera>
{
	//friend class Singleton<Camera>;

public:
	/**
	* @brief �R���X�g���N�^
	*/
	Camera();

	/**
	* @brief �R���X�g���N�^
	*/
	Camera(D3DXVECTOR3 pos_, D3DXVECTOR3 lookAt_, D3DXVECTOR3 upVec_, float distance_);

	/**
	* @brief �f�X�g���N�^
	*/
	~Camera();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @brief �Ώۂ�����悤�ɃJ�����̈ʒu���Z�b�g����
	* @param[in] pos_ �ΏۂƂȂ�I�u�W�F�N�g 
	* @param[in] distance_  �J�����Ɨ�������
	*/
	void SetCamera(const D3DXVECTOR3& pos_, float distance_);

	/**
	* @brief �O�����̃x�N�g����Ԃ��֐�
	* @return D3DXVECTOR3 �O�����x�N�g��
	*/
	D3DXVECTOR3  GetForwardVec()const;

	/**
	* @brief �������̃x�N�g����Ԃ��֐�
	* @return D3DXVECTOR3 �������x�N�g��
	*/
	D3DXVECTOR3  GetLeftVec()const;

	/**
	* @brief �`���Ԃ��֐�
	* @return Shape*
	*/
	Shape* GetShape()const				 { return m_Shape;   }

	/**
	* @brief �J�����̍��W��Ԃ��֐�
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetPos()const     { return &m_Pos;    }
	
	/**
	* @brief �J�����̒����_��Ԃ��֐�
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetLookAt()const  { return &m_LookAt; }
	
	/**
	* @brief �J�����̏�����x�N�g����Ԃ��֐�
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetUpVec()const   { return &m_UpVec;  }
	
private:
	/**
	* @brief �J�����̉�]�֐�
	*/
	void Rotate();

	/**
	* @brief �r���[���W�ϊ�
	*/
	void SetViewMatrix();

	/**
	* @brief �v���W�F�N�V�������W�ϊ�
	*/
	void SetProjectionMatrix();

	D3DXVECTOR3 m_Pos;		//! �J�����̍��W
	D3DXVECTOR3 m_LookAt;	//! �����_
	D3DXVECTOR3 m_UpVec;	//! �J�����̏�����x�N�g��
	float m_Distance;		//! ����

	float m_Yaw;			//! X����]
	float m_Pitch;			//! Y����]

	D3DXVECTOR2 m_Sensitivity;	//! �J�������x

	Shape* m_Shape;			//! �`��
};

#endif