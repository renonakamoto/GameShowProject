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

	int Row;		//!< �s
	int Column;		//!< ��
};

struct Node
{
	Node()
	{
	}

	Node(int row, int column) : Cell(row, column)
	{
	}

	Cell Cell;						//!< �m�[�h�̈ʒu
	std::vector<Node*> Edges;		//!< �אڃm�[�h
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

	Node* Node;		//!< �m�[�h
	float Cost;		//!< �R�X�g
};

class Navigator
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	Navigator();

	/**
	* @biref �f�X�g���N�^
	*/
	~Navigator();

	/**
	* @biref �G�l�~�[�̏��񃋁[�g�擾�֐�
	* �G�l�~�[�Ɏ��g�̏��񃋁[�g�������܂�
	* @return ���[�g��^����ꂽ��true�A���[�g�񋟂Ɏ��s������false
	*/
	bool GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_);

	/**
	* @biref �}�b�v�̈ړ��\���̏���^���܂�
	* @return ����^����ꂽ��true�A���s������false
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
