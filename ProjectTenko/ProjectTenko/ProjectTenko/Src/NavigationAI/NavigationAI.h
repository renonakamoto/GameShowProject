#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"

struct EnemyRoute
{
	std::string Name;
	std::vector<float> RouteList;
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
	bool GetEnemyRoute(std::string Name_);

	/**
	* @biref マップの移動可能個所の情報を与えます
	* @return 情報を与えられたらtrue、失敗したらfalse
	*/
	bool GetMapData();

private:
	bool LoadResouces();

private:
	std::vector <EnemyRoute> m_EnemyRoute;

};

#endif // !NAVIGATIONAI_H_
