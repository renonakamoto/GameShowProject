#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "GameObject.h"
#include "../Shape/Shape3D.h"

class Object3D : public GameObject
{
public:
	Object3D() :
		Object3D({ 0,0,0 }, { 0,0,0 }, { 1,1,1 })
	{}

	Object3D(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_, { 0,0,0 }, { 1,1,1 })
	{}

	Object3D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		GameObject(pos_, rot_, scale_),
		m_Shape(nullptr)
	{}

	~Object3D()
	{
		delete m_Shape;
		m_Shape = nullptr;
	}

	void Update() = 0;
	void Draw() = 0;

protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	
public:
	Shape3D* GetShape() { return m_Shape; }

protected:
	Shape3D* m_Shape;
	
	
};


#endif