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

	void SetCamera(const D3DXVECTOR3& pos_, float distance_);

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

	//! X軸回転
	float m_Yaw;

	//! Y軸回転
	float m_Pitch;

	//! カメラ感度
	float m_Sensitivity;

	//! 距離
	float m_Distance;

};

#endif