#include "NavigationAI.h"

Navigator::Navigator()
{
}

Navigator::~Navigator()
{
}

bool Navigator::GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_)
{
	for (auto& e : m_Route)
	{
		if (name_ == e.at(0))
		{
			for (int i = 1; i < e.size(); i + 3)
			{
				D3DXVECTOR3 vec3 = { std::stoi(e.at(i)), std::stoi(e.at(i + 1)), std::stoi(e.at(i + 2)) };
				route_.push_back(vec3);
			}

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
	Csv csv;
	std::string route("");
	std::string path("");

	if (csv.Load(route, m_Route) && csv.Load(path, m_MovingPath))
	{
		return true;
	}
	return false;
}
