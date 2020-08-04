#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <d3dx9.h>

struct Cell
{
	Cell() : m_Row(-1), m_Column(-1)
	{
	}

	Cell(int row, int column) : m_Row(row), m_Column(column)
	{
	}

	int m_Row;			//!< �s
	int m_Column;		//!< ��
};

struct Node
{
	Node()
	{
	}

	Node(int row, int column) : m_Cell(row, column)
	{
	}

	Node(Cell cell_) : m_Cell(cell_)
	{
	}


	Cell m_Cell;						//!< �m�[�h�̈ʒu
	std::vector<Node*> m_Edges;			//!< �אڃm�[�h
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

	void AddPos(std::vector<D3DXVECTOR3>& route_, float size_) const;

	Node* m_Node;
	float m_Cost;
	Route* m_Parent;
};

#endif // !NODE_H_
