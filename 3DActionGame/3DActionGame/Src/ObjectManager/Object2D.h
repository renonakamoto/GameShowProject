#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include <d3d11.h>
#include "GameObject.h"

class Object2D : public GameObject
{
public:
	Object2D()
	{}

	Object2D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		GameObject(pos_, rot_, scale_)
	{}

	Object2D(DirectX::XMFLOAT3 pos_) :
		GameObject(pos_)
	{}

	virtual void Init()   = 0;
	virtual void Update() = 0;
	virtual void Draw()   = 0;

protected:
	virtual void Release() = 0;
	
};

#endif