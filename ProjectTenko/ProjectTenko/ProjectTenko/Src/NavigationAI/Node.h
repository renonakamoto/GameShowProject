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

	Cell m_Cell;						//!< �m�[�h�̈ʒu
	D3DXVECTOR3 m_Pos;					//!< �m�[�h�̒��S���W
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

	/**
	* @biref ���W�ǉ��֐�
	* ���g�̃m�[�h�̍��W���R���e�i�ɒǉ�����֐��ł�
	* @param[out] route_ ���W��ǉ�����R���e�i
	*/
	void AddPos(std::vector<D3DXVECTOR3>& route_) const;

	Node* m_Node;		//!< �m�[�h�̃|�C���^
	float m_Cost;		//!< �q���[���X�e�B�b�N�R�X�g
	Route* m_Parent;	//!< �o�H�̐e�ƂȂ�Route�̃|�C���^
};

#endif // !NODE_H_
