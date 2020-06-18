#include "FlexibleCollision.h"

bool FlexibleCollision::Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_)
{
	for (int i = 0; i < s1_.size(); ++i)
	{
		for (int j = 0; j < s2_.size(); ++j)
		{
			if (m_CollisionTable[(int)s1_[i]->GetType()][(int)s2_[j]->GetType()] == nullptr)
			{
				continue;
			}

			if (m_CollisionTable[(int)s1_[i]->GetType()][(int)s2_[j]->GetType()]->Test(*s1_[i], *s2_[j]) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool FlexibleCollision::Test(const Shape& s1_, const Shape& s2_)
{
	if (m_CollisionTable[(int)s1_.GetType()][(int)s2_.GetType()] == nullptr)
	{
		return false;
	}

	if (m_CollisionTable[(int)s1_.GetType()][(int)s2_.GetType()]->Test(s1_, s2_) == true)
	{
		return true;
	}

	return false;
}