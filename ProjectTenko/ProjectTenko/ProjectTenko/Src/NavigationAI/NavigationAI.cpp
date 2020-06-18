#include "NavigationAI.h"

Navigator::Navigator()
{
}

Navigator::~Navigator()
{
}

bool Navigator::GetEnemyRoute(std::string Name_)
{
	for (auto e : m_EnemyRoute)
	{
		if (Name_ == e.Name)
		{
			return true;
		}
	}

	return false;
}

bool Navigator::GetMapData()
{
	return false;
}

bool Navigator::LoadResouces()
{
	return false;
}
