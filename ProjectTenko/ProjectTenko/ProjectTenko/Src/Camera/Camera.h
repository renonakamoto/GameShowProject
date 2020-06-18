#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Collision/Shape/Shape.h"
#include <d3dx9.h>

class ObjectBase;

/**
* @brief �J�����N���X
* @details �ڍׂȃN���X�̐���
*/
class Camera
{
public:
	Camera();
	~Camera();

	void Update();
	void Move();
	void Rotate();

	void SetCamera(const D3DXVECTOR3& pos_, float distance_);
	void SetCameraSensitivity(float horizon_, float vertical_);
	
	D3DXVECTOR3  GetForwardVec();
	D3DXVECTOR3  GetLeftVec();

	Shape* GetShape() {return m_Shape;}
	const D3DXVECTOR3* GetPos()const     { return &m_Pos;    }
	const D3DXVECTOR3* GetLookAt()const  { return &m_LookAt; }
	const D3DXVECTOR3* GetUpVec()const   { return &m_UpVec;  }
	
private:
	void SetViewMatrix();
	void SetProjectionMatrix();

	D3DXVECTOR3 m_Pos;		//! �J�����̍��W
	D3DXVECTOR3 m_LookAt;	//! �����_
	D3DXVECTOR3 m_UpVec;	//! �J�����̏�����x�N�g��
	float m_Distance;		//! ����

	float m_Yaw;			//! X����]
	float m_Pitch;			//! Y����]

	D3DXVECTOR2 m_Sensitivity;

	Shape* m_Shape;
};

#endif