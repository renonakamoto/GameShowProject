#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_

#include "../Engine/Fbx/FbxManager.h"
#include "../Collision/Shape/Shape.h"
#include <d3dx9.h>
#include <string>
#include <vector>

class ObjectBase
{
public:
	ObjectBase(D3DXVECTOR3 pos_, std::string key_) :
		m_Pos   (pos_),
		m_FbxKey(key_),
		m_Angle (0.f),
		m_Width (0.f),
		m_Height(0.f),
		m_Depth (0.f)
	{}

	ObjectBase(D3DXVECTOR3 pos_, std::string key_, float width_, float height_, float depth_) :
		m_Pos   (pos_),
		m_FbxKey(key_),
		m_Width (width_),
		m_Height(height_),
		m_Depth (depth_),
		m_Angle (0.f)
	{}

	virtual ~ObjectBase() 
	{
		for(int i = 0; i < m_Shape.size(); i++)
		{ 
			delete m_Shape[i];
		}

		m_Shape.clear();
	}

	virtual void Update() {}
	virtual void Draw() {}

	D3DXVECTOR3 GetPos() const { return m_Pos; }

	std::vector<Shape*> GetShape() const    { return m_Shape; }

	float GetAngle() const     { return m_Angle; }

protected:
	D3DXVECTOR3 m_Pos;
	D3DXMATRIX  m_Mat_World;

	float		m_Angle;

	float		m_Width;
	float		m_Height;
	float		m_Depth;

	std::vector<Shape*> m_Shape;

	std::string m_FbxKey;

};

#endif