#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "ObjectBase.h"
#include <DirectXMath.h>

class GameObject : public ObjectBase
{
public:
	GameObject() :
		m_Pos{ 0,0,0 },
		m_Rot{ 0,0,0 },
		m_Scale{ 1,1,1 }
	{}
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	

protected:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Rot;
	DirectX::XMFLOAT3 m_Scale;

};

#endif