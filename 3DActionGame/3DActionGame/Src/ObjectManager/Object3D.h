#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "GameObject.h"

class Object3D : public GameObject
{
public:
	
	void Update() = 0;
	void Draw() = 0;
	

protected:
	virtual void Init() = 0;
	virtual void Release() = 0;
	
};


#endif