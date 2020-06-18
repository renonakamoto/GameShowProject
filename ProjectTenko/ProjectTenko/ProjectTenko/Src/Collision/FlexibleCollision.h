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
		int shape_aabb	   = (int)SHAPE_TYPE::Shape_AABB;
		int shape_cylinder = (int)SHAPE_TYPE::Shape_Cylinder;
		int shape_ray      = (int)SHAPE_TYPE::Shape_Ray;
		// 当たり判定テーブルの作成
		m_CollisionTable[shape_aabb][shape_aabb]			= new AABBAndAABB();
		m_CollisionTable[shape_aabb][shape_cylinder]		= new AABBandCylinder();
		m_CollisionTable[shape_aabb][shape_ray]				= new AABBandRay();

		m_CollisionTable[shape_cylinder][shape_cylinder]	= nullptr;
		m_CollisionTable[shape_cylinder][shape_aabb]		= new AABBandCylinder();
		m_CollisionTable[shape_cylinder][shape_ray]			= new CylinderAndRay();

		m_CollisionTable[shape_ray][shape_ray]				= nullptr;
		m_CollisionTable[shape_ray][shape_aabb]				= new AABBandRay();
		m_CollisionTable[shape_ray][shape_cylinder]			= new CylinderAndRay();
		
	}
	
	virtual ~FlexibleCollision() 
	{
		int shape_num = (int)SHAPE_TYPE::Shape_Type_Num;

		for (int i = 0; i < shape_num; ++i) {
			for (int j = 0; j < shape_num; ++j) {
				if (m_CollisionTable[i][j] != nullptr) {
					delete m_CollisionTable[i][j];
				}
			}
		}
	}

	bool Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_);
	bool Test(const Shape& s1_, const Shape& s2_);


private:
	//! 当たりテーブル
	Collision* m_CollisionTable[(int)SHAPE_TYPE::Shape_Type_Num][(int)SHAPE_TYPE::Shape_Type_Num];
};

#endif