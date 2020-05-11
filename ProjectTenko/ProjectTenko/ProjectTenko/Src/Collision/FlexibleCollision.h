#ifndef FLEXIBLECOLLISION_H_
#define FLEXIBLECOLLISION_H_

#include "Collision.h"
#include "Shape/Shape.h"

//#define A static_cast<int>(SHAPE_TYPE::Shape_Type_Num)

class FlexibleCollision : public Collision
{
public:
	FlexibleCollision() 
	{
		m_CollisionTable[ShapeAABB][ShapeAABB]     = new AABBAndAABB();
		m_CollisionTable[ShapeAABB][ShapeCylinder] = new AABBandCylinder();
		m_CollisionTable[ShapeCylinder][ShapeAABB] = new AABBandCylinder();
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

	bool Test(const Shape& s1_, const Shape& s2_)
	{
		int s1_type = static_cast<int>(s1_.GetType());
		int s2_type = static_cast<int>(s2_.GetType());
		return m_CollisionTable[s1_type][s2_type]->Test(s1_, s2_);
	}


private:
	static const int ShapeAABB	   = static_cast<int>(SHAPE_TYPE::Shape_AABB);
	static const int ShapeCylinder = static_cast<int>(SHAPE_TYPE::Shape_Cylinder);
	static const int ShapeNum	   = static_cast<int>(SHAPE_TYPE::Shape_Type_Num);

	//! ������e�[�u��
	Collision* m_CollisionTable[ShapeNum][ShapeNum];
};

#endif