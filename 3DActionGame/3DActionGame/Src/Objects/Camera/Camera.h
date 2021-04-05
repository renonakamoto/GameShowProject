#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../ObjectManager/GameObject.h"

class Camera : public GameObject
{
public:
	Camera() :
		Camera({ 0.0f,0.0f,0.0f })
	{}

	Camera(DirectX::XMFLOAT3 lookAt_) :
		m_LookAt(lookAt_)
	{
		Init();
	}
	
	
	~Camera()
	{
		Release();
	}

	virtual void Update();
	virtual void Draw();

	void SetLookAtPos(DirectX::XMFLOAT3 pos_) { m_LookAt = pos_; }

	DirectX::XMFLOAT3 GetFowardNormal();

	DirectX::XMFLOAT3 GetLeftNormal();
	
protected:
	virtual void Init();
	virtual void Release();

protected:
	DirectX::XMFLOAT3 m_LookAt;
	DirectX::XMMATRIX m_ProjMat;
	
};

#endif