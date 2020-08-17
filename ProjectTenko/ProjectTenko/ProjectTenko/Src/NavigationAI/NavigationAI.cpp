#include "NavigationAI.h"
#include "..//ExternalFle/Csv/Csv.h"
#include <list>
#include <math.h>

std::vector<std::vector<std::string>> Navigator::m_MovingPath;
std::vector<std::vector<Node>> Navigator::m_Graph;

Navigator::Navigator()
{
	LoadResouces();
	CreateGraph();
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
			for (int i = 1; i < e.size(); i = i + 3)
			{
				D3DXVECTOR3 vec3 = { std::stof(e.at(i)), std::stof(e.at(i + 1)), std::stof(e.at(i + 2)) };
				route_.push_back(vec3);
			}

			return true;
		}
	}

	return false;
}

unsigned __stdcall Navigator::GetReturnRoute(void* data_)
{
	NavData* data = static_cast<NavData*>(data_);

	std::list<Route> open_list;
	std::list<Route> close_list;

	float cellsize = std::stof(m_MovingPath[0][2]);

	Route start(
		&m_Graph[static_cast<int>(fabsf(data->Pos.x / cellsize))][static_cast<int>(fabsf(data->Pos.z / cellsize))],
		0.0f);
	Cell goal_cell(static_cast<int>(fabsf(data->Goal.x / cellsize)), static_cast<int>(fabsf(data->Goal.z / cellsize)));

	open_list.push_back(start);

	while (open_list.empty() == false)
	{
		auto route = open_list.begin();

		if (IsEqualCell(route->m_Node->m_Cell, m_Graph[goal_cell.m_Row][goal_cell.m_Column].m_Cell))
		{
			close_list.push_back(*route);
			break;
		}

		for (Node* node : route->m_Node->m_Edges)
		{
			float hcost = CalculateHeruristicCost(node, &m_Graph[goal_cell.m_Row][goal_cell.m_Column]);
			float cost = hcost + route->m_Cost;

			AddRoute(open_list, close_list, *route, node, cost);
		}

		close_list.push_back(*route);

		open_list.erase(route);
	}

	close_list.back().AddPos(data->Route, cellsize);

	return 0;
}

bool Navigator::LoadResouces()
{
	Csv csv;
	std::string route("assets/Csv/EnemyMovementPoint.csv");
	std::string path("assets/Csv/MovingPath.csv");

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
				if (IsCellInRange(cell.m_Row, cell.m_Column, row, column) &&
					std::stoi(m_MovingPath[pos][counter]) == 1)
				{
					m_Graph[i][j].m_Edges.push_back(&m_Graph[cell.m_Row][cell.m_Column]);
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

bool Navigator::IsEqualCell(const Cell& a, const Cell& b)
{
	if (a.m_Column == b.m_Column &&
		a.m_Row == b.m_Row)
	{
		return true;
	}
	return false;
}

float Navigator::CalculateHeruristicCost(const Node* node_, const Node* goal_)
{
	float column = fabsf(goal_->m_Cell.m_Column - node_->m_Cell.m_Column);
	float row = fabsf(goal_->m_Cell.m_Row - node_->m_Cell.m_Row);
	return sqrtf(column * column + row * row);
}

void Navigator::AddRoute(std::list<Route>& open_, std::list<Route>& close_, Route& current_, Node* add_, float cost_)
{
	bool is_same_route_open = false;
	bool is_same_route_close = false;

	for (auto itr = close_.begin(); itr != close_.end(); itr++)
	{
		if (IsEqualCell(add_->m_Cell, itr->m_Node->m_Cell))
		{
			is_same_route_close = true;

			if (cost_ < itr->m_Cost)
			{
				close_.erase(itr);
				open_.push_back(Route(add_, cost_, &current_));

				open_.sort();
				return;
			}
		}
	}

	for (auto itr = open_.begin(); itr != open_.end(); itr++)
	{
		if (IsEqualCell(add_->m_Cell, itr->m_Node->m_Cell))
		{
			is_same_route_open = true;

			if (cost_ < itr->m_Cost)
			{
				open_.erase(itr);
				open_.push_back(Route(add_, cost_, &current_));

				open_.sort();
				return;
			}
		}
	}

	if (is_same_route_close == false && is_same_route_open == false)
	{
		open_.push_back(Route(add_, cost_, &current_));
		open_.sort();
	}
}
