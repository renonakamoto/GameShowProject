#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_

#include "../Engine/Fbx/FbxManager.h"
#include <d3dx9.h>
#include <string>

class ObjectBase
{
public:
	ObjectBase(D3DXVECTOR3 pos_, std::string key_) :
		m_Pos(pos_),
		m_FbxKey(key_),
		m_Angle(0.f)
	{
	}

	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	D3DXVECTOR3 GetPos() const;

protected:
	D3DXVECTOR3 m_Pos;
	D3DXMATRIX  m_Mat_World;

	float		m_Angle;
	
	std::string m_FbxKey;

};

#endif