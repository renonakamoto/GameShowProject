#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"
#include "Node.h"
#include <string>
#include <vector>
#include <list>
#include <d3dx9.h>

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
	void GetReturnRoute(D3DXVECTOR3& pos_, D3DXVECTOR3& goal_, std::vector<D3DXVECTOR3>& route_);

	bool LoadResouces();

	void CreateGraph();

private:
	bool IsCellInRange(int row_, int column_, int width_, int height_);

	bool IsEqualCell(const Cell& a, const Cell& b);

	float CalculateHeruristicCost(const Node* node_, const Node* goal_);

	void AddRoute(std::list<Route>& open_, std::list<Route>& close_, Route& current_, Node* add_, float cost);

private:
	std::vector<std::vector<std::string>> m_Route;
	std::vector<std::vector<std::string>> m_MovingPath;
	std::vector<std::vector<Node>> m_Graph;
};

#endif // !NAVIGATIONAI_H_
