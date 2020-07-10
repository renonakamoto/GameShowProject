#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"
#include <string>
#include <vector>
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
	bool GetMapData();

private:
	bool LoadResouces();

private:
	std::vector<std::vector<std::string>> m_Route;
	std::vector<std::vector<std::string>> m_MovingPath;
};

#endif // !NAVIGATIONAI_H_
