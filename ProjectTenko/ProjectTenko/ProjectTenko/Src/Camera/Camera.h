#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

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

	void SetViewMatrix();
	void SetProjectionMatrix();
	

	D3DXVECTOR3* GetPos()    { return &m_Pos; }
	D3DXVECTOR3* GetLookAt() { return &m_LookAt; }
	D3DXVECTOR3* GetUpVec()  { return &m_UpVec; }	
	
private:

	D3DXVECTOR3 m_Pos;		//! �J�����̍��W
	D3DXVECTOR3 m_LookAt;	//! �����_
	D3DXVECTOR3 m_UpVec;	//! �J�����̏�����x�N�g��
	float m_Distance;		//! ����

	float m_Yaw;			//! X����]
	float m_Pitch;			//! Y����]

	float m_Sensitivity;	//! �J�������x

};

#endif