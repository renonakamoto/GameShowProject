#include "NavigationAI.h"
#include <list>

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
				D3DXVECTOR3 vec3 = { std::stof(e.at(i)), std::stof(e.at(i + 1)), std::stof(e.at(i + 2)) };
				route_.push_back(vec3);
			}

			return true;
		}
	}

	return false;
}

bool Navigator::GetReturnRoute(D3DXVECTOR3& pos_, D3DXVECTOR3& goal_, std::vector<D3DXVECTOR3>& route_)
{
	std::list<Route> open_list;
	std::list<Route> close_list;


	// open_list.push_back(Route);

	while (!open_list.empty())
	{
		auto route = open_list.begin();


	}

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

void Navigator::CreateGraph()
{
	int column = std::stoi(m_MovingPath[0][0]);
	int row = std::stoi(m_MovingPath[0][1]);

	int pos = 1;

	for (int i = 0; i < row; i++)
	{
		std::vector<Node> line;

		for (int j = 0; j < column; j++)
		{
			line.push_back(Node(j, i));
		}
		m_Graph.push_back(line);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			Cell surround[] =
			{
				Cell(column, row - 1),
				Cell(column + 1, row - 1),
				Cell(column + 1, row),
				Cell(column + 1, row + 1),
				Cell(column, row + 1),
				Cell(column - 1, row + 1),
				Cell(column - 1, row),
				Cell(column - 1, row - 1)
			};

			int counter = 3;

			for (const Cell& cell : surround)
			{
				if (IsCellInRange(cell.Row, cell.Column, row, column) &&
					std::stoi(m_MovingPath[pos][counter]) == 1)
				{
					m_Graph[i][j].Edges.push_back(&m_Graph[cell.Row][cell.Column]);
				}
				pos++;
				counter++;
			}
		}
	}
}

bool Navigator::IsCellInRange(int row_, int column_, int width_, int height_)
{
	if (row_ >= 0 && row_ < width_ && column_ >= 0 && column_ < height_)
	{
		return true;
	}

	return false;
}
