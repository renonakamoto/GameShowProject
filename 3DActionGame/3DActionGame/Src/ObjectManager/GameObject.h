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

	GameObject(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		m_Pos(pos_),
		m_Rot(rot_),
		m_Scale(scale_)
	{}

	GameObject(DirectX::XMFLOAT3 pos_) :
		m_Pos(pos_),
		m_Rot{ 0,0,0 },
		m_Scale{ 1,1,1 }
	{}

	virtual void Update() = 0;
	virtual void Draw() = 0;

public:
	void SetPos(DirectX::XMFLOAT3 pos_) { m_Pos = pos_; }
	DirectX::XMFLOAT3 GetPos() { return m_Pos; }
	
protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	

protected:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Rot;
	DirectX::XMFLOAT3 m_Scale;

};

#endif