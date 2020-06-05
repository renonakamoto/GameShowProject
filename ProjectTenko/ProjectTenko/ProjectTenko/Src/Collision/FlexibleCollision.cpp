#include "FlexibleCollision.h"


bool FlexibleCollision::Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_)
{
	for (int i = 0; i < s1_.size(); ++i)
	{
		for (int j = 0; j < s2_.size(); ++j)
		{

			if (m_CollisionTable[(int)s1_[i]->GetType()][(int)s2_[j]->GetType()]->Test(*s1_[i], *s2_[j]) == true)
			{
				return true;
			}
		}
	}

	return false;
}