#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"
#include <string>
#include <vector>
#include <d3dx9.h>

struct Cell
{
	Cell() : Row(-1), Column(-1)
	{
	}

	Cell(int row, int column) : Row(row), Column(column)
	{
	}

	int Row;		//!< 行
	int Column;		//!< 列
};

struct Node
{
	Node()
	{
	}

	Node(int row, int column) : Cell(row, column)
	{
	}

	Cell Cell;						//!< ノードの位置
	std::vector<Node*> Edges;		//!< 隣接ノード
};

struct Route
{
	Route(Node* node, float cost) : Node(node), Cost(cost)
	{
	}

	bool operator<(const Route& route) const
	{
		return Cost < route.Cost;
	}

	Node* Node;		//!< ノード
	float Cost;		//!< コスト
};

class Navigator
{
public:
	/**
	* @biref コンストラクタ
	*/
	Navigator();

	/**
	* @biref デストラクタ
	*/
	~Navigator();

	/**
	* @biref エネミーの巡回ルート取得関数
	* エネミーに自身の巡回ルートを教えます
	* @return ルートを与えられたらtrue、ルート提供に失敗したらfalse
	*/
	bool GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_);

	/**
	* @biref マップの移動可能個所の情報を与えます
	* @return 情報を与えられたらtrue、失敗したらfalse
	*/
	bool GetReturnRoute(D3DXVECTOR3& pos_, D3DXVECTOR3& goal_, std::vector<D3DXVECTOR3>& route_);

	bool LoadResouces();

	void CreateGraph();

private:
	bool IsCellInRange(int row_, int column_, int width_, int height_);

private:
	std::vector<std::vector<std::string>> m_Route;
	std::vector<std::vector<std::string>> m_MovingPath;
	std::vector<std::vector<Node>> m_Graph;
};

#endif // !NAVIGATIONAI_H_
