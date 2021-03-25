#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include <d3d11.h>
#include "GameObject.h"

class Object2D : public GameObject
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	virtual void Init() = 0;
	virtual void Release() = 0;

private:
	
	
};

#endif