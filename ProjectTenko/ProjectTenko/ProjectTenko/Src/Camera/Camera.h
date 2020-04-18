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

	//! �J�����̍��W
	D3DXVECTOR3 m_Pos;

	//! �����_
	D3DXVECTOR3 m_LookAt;

	//! �J�����̏�����x�N�g��
	D3DXVECTOR3 m_UpVec;

	//! X����]
	float m_Yaw;

	//! Y����]
	float m_Pitch;

	//! �J�������x
	float m_Sensitivity;

	//! ����
	float m_Distance;

};

#endif