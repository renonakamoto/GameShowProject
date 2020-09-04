#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <memory>
#include <d3dx9.h>

struct Cell
{
	Cell() : m_Row(-1), m_Column(-1)
	{
	}

	Cell(int row, int column) : m_Row(row), m_Column(column)
	{
	}

	int m_Row;			//!< 行
	int m_Column;		//!< 列
};

struct Node
{
	Node()
	{
	}

	Node(int row, int column) : m_Cell(row, column)
	{
	}

	Node(int row, int column, float x_, float y_, float z_) : m_Cell(row, column), m_Pos(x_, y_, z_)
	{
	}

	Node(Cell cell_) : m_Cell(cell_)
	{
	}

	Node(Cell cell_, D3DXVECTOR3 pos_) : m_Cell(cell_), m_Pos(pos_)
	{
	}

	void AddPos(std::vector<D3DXVECTOR3>& route_) const;

	Cell m_Cell;						//!< ノードの位置
	D3DXVECTOR3 m_Pos;					//!< ノードの中心座標
	std::vector<Node*> m_Edges;			//!< 隣接ノード
};

struct Route
{
	Route(Node* node_, float cost_) :
		m_Node(node_),
		m_Cost(cost_),
		m_Parent(nullptr)
	{
	}

	Route(Node* node_, float cost_, Route* parent_) :
		m_Node(node_),
		m_Cost(cost_),
		m_Parent(parent_)
	{
	}


	bool operator<(const Route& route) const
	{
		return m_Cost < route.m_Cost;
	};

	/**
	* @biref 座標追加関数
	* 自身のノードの座標をコンテナに追加する関数です
	* @param[out] route_ 座標を追加するコンテナ
	*/
	void AddPos(std::vector<D3DXVECTOR3>& route_) const;

	Node* m_Node;		//!< ノードのポインタ
	float m_Cost;		//!< ヒューリスティックコスト
	Route* m_Parent;	//!< 経路の親となるRouteのポインタ
};

#endif // !NODE_H_
