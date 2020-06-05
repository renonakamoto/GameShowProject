#ifndef FLEXIBLECOLLISION_H_
#define FLEXIBLECOLLISION_H_

#include "Collision.h"
#include "Shape/Shape.h"
#include <vector>

class Shape;

class FlexibleCollision
{
public:
	FlexibleCollision() 
	{
		m_CollisionTable[ShapeAABB][ShapeAABB]     =     new AABBAndAABB();
		m_CollisionTable[ShapeAABB][ShapeCylinder] =     new AABBandCylinder();
		m_CollisionTable[ShapeCylinder][ShapeAABB] =     new AABBandCylinder();
		m_CollisionTable[ShapeCylinder][ShapeCylinder] = new AABBAndAABB();
	}
	
	virtual ~FlexibleCollision() 
	{
		for (int i = 0; i < ShapeNum; ++i) {
			for (int j = 0; j < ShapeNum; ++j) {
				if (m_CollisionTable[i][j] != nullptr) {
					delete m_CollisionTable[i][j];
				}
			}
		}
	}

	bool Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_);


private:
	static const int ShapeAABB	   = static_cast<int>(SHAPE_TYPE::Shape_AABB);
	static const int ShapeCylinder = static_cast<int>(SHAPE_TYPE::Shape_Cylinder);
	static const int ShapeNum	   = static_cast<int>(SHAPE_TYPE::Shape_Type_Num);

	//! ìñÇΩÇËÉeÅ[ÉuÉã
	Collision* m_CollisionTable[ShapeNum][ShapeNum];
};

#endif