#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//Utility/Singleton.h"
#include "Node.h"
#include <string>
#include <vector>
#include <list>
#include <d3dx9.h>

struct NavData
{
	std::vector<D3DXVECTOR3> &Route;
	D3DXVECTOR3& Pos;
	D3DXVECTOR3& Goal;
};

class Navigator : public Singleton<Navigator>
{
public:

	friend Singleton<Navigator>;

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
	static unsigned __stdcall GetReturnRoute(void* data_);

	bool LoadResouces();

	void CreateGraph();

private:

	/**
	* @biref �R���X�g���N�^
	*/
	Navigator();

	/**
	* @biref �f�X�g���N�^
	*/
	~Navigator();


	bool IsCellInRange(int row_, int column_, int width_, int height_);

	static bool IsEqualCell(const Cell& a, const Cell& b);

	static float CalculateHeruristicCost(const Node* node_, const Node* goal_);

	static void AddRoute(std::list<Route>& open_, std::list<Route>& close_, Route& current_, Node* add_, float cost);

private:
	std::vector<std::vector<std::string>> m_Route;
	static std::vector<std::vector<std::string>> m_MovingPath;
	static std::vector<std::vector<Node>> m_Graph;
};

#endif // !NAVIGATIONAI_H_
