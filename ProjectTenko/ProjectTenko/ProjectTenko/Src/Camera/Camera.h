#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3dx9.h>

/**
* @brief カメラクラス
* @details 詳細なクラスの説明
*/
class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	void Move();
	void Rotate();

	void SetViewMatrix();
	void SetProjectionMatrix();
	

	D3DXVECTOR3* GetPos()    { return &m_Pos; }
	D3DXVECTOR3* GetLookAt() { return &m_LookAt; }
	D3DXVECTOR3* GetUpVec()  { return &m_UpVec; }	
	
private:

	//! カメラの座標
	D3DXVECTOR3 m_Pos;

	//! 注視点
	D3DXVECTOR3 m_LookAt;

	//! カメラの上向きベクトル
	D3DXVECTOR3 m_UpVec;

	float m_Yaw;

	float m_Pitch;

};

#endif