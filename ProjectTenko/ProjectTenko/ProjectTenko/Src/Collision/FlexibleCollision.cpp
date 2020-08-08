#include "FlexibleCollision.h"

FlexibleCollision::FlexibleCollision()
{
	int shape_aabb     = static_cast<int>(SHAPE_TYPE::Shape_AABB);
	int shape_cylinder = static_cast<int>(SHAPE_TYPE::Shape_Cylinder);
	int shape_ray      = static_cast<int>(SHAPE_TYPE::Shape_Ray);
	// ìñÇΩÇËîªíËÉeÅ[ÉuÉãÇÃçÏê¨
	m_CollisionTable[shape_aabb][shape_aabb]     = new AABBAndAABB();
	m_CollisionTable[shape_aabb][shape_cylinder] = new AABBAndCylinder();
	m_CollisionTable[shape_aabb][shape_ray]      = new AABBandRay();

	m_CollisionTable[shape_cylinder][shape_cylinder] = nullptr;
	m_CollisionTable[shape_cylinder][shape_aabb]	 = new AABBAndCylinder();
	m_CollisionTable[shape_cylinder][shape_ray]		 = new CylinderAndRay();

	m_CollisionTable[shape_ray][shape_ray]      = nullptr;
	m_CollisionTable[shape_ray][shape_aabb]		= new AABBandRay();
	m_CollisionTable[shape_ray][shape_cylinder] = new CylinderAndRay();
}

FlexibleCollision::~FlexibleCollision()
{
	int shape_num = static_cast<int>(SHAPE_TYPE::Shape_Type_Num);

	for (int i = 0; i < shape_num; ++i) {
		for (int j = 0; j < shape_num; ++j) {
			if (m_CollisionTable[i][j] != nullptr) {
				delete m_CollisionTable[i][j];
			}
		}
	}
}

bool FlexibleCollision::Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_)
{
	for (size_t i = 0; i < s1_.size(); ++i)
	{
		for (size_t j = 0; j < s2_.size(); ++j)
		{
			if (m_CollisionTable[static_cast<int>(s1_[i]->GetType())][static_cast<int>(s2_[j]->GetType())] == nullptr)
			{
				continue;
			}

			if (m_CollisionTable[static_cast<int>(s1_[i]->GetType())][static_cast<int>(s2_[j]->GetType())]->Test(s1_[i], s2_[j]) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool FlexibleCollision::Test(const Shape& s1_, const Shape& s2_)
{
	if (m_CollisionTable[static_cast<int>(s1_.GetType())][static_cast<int>(s2_.GetType())] == nullptr)
	{
		return false;
	}

	if (m_CollisionTable[static_cast<int>(s1_.GetType())][static_cast<int>(s2_.GetType())]->Test(&s1_, &s2_) == true)
	{
		return true;
	}

	return false;
}