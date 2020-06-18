#ifndef SIMPLECOLLISION_H_
#define SIMPLECOLLISION_H_

#include <d3dx9.h>

class SimpleCollision
{
public:
	static bool HitRectAndPoint(D3DXVECTOR2 rectPos_, float width_, float height_, D3DXVECTOR2 pointPos_)
	{
		if (pointPos_.x >= rectPos_.x && pointPos_.x <= (rectPos_.x + width_) &&
			pointPos_.y >= rectPos_.y && pointPos_.y <= (rectPos_.y + height_))
		{
			return true;
		}
		
		return false;
	}

};

#endif