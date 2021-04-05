#ifndef FOLLOW_CAMERA_H_
#define FOLLOW_CAMERA_H_

#include "Camera.h"

class FollowCamera : public Camera
{
public:
	FollowCamera():
		m_Distance(0.f),
		m_Yaw(0.f),
		m_Pitch(0.f),
		m_Height(9.f)
	{}

	void Update() override;

	void SetFollowObject(GameObject* object_) { m_FollowObject = object_; }

	void SetDistance(float distance_) { m_Distance = distance_; }
	
	void SetOffset(DirectX::XMFLOAT3 offset_) { m_Offset = offset_; }

private:
	float m_Distance;	//! オブジェクトとの距離
	float m_Yaw;		//! Y軸回転の角度
	float m_Pitch;
	float m_Height;		//! 高さ
	DirectX::XMFLOAT3 m_Offset;
	GameObject* m_FollowObject;
};

#endif