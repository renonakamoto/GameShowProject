#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "GameObject.h"

class Object3D : public GameObject
{
public:
	Object3D() :
		GameObject({ 0,0,0 }, { 0,0,0 }, { 1,1,1 })
	{}

	Object3D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		GameObject(pos_, rot_, scale_)
	{}

	Object3D(DirectX::XMFLOAT3 pos_) :
		GameObject(pos_)
	{}

	~Object3D()
	{}

	void Update() = 0;
	void Draw() = 0;
	

protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	
};


#endif