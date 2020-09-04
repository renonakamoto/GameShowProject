#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//Utility/Singleton.h"
#include "Node.h"
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <d3dx9.h>

struct NavData
{
	std::vector<D3DXVECTOR3> Route;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Goal;
};

class Navigator : public Singleton<Navigator>
{
public:

	friend Singleton<Navigator>;

	/**
	* @biref エネミーの巡回ルート取得関数
	* エネミーに自身の巡回ルートを教えます
	* @return ルートを与えられたらtrue、ルート提供に失敗したらfalse
	* @param[in] name_	エネミーの名前
	* @param[out] route_ エネミーの巡回ルート格納用コンテナ
	*/
	bool GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_);

	/**
	* @biref マップの移動可能個所の情報を与えます
	* @return 情報を与えられたらtrue、失敗したらfalse
	* @param[in] data_ 始点、終点、帰還経路格納用コンテナを持ったNavData型構造体
	*/
	static unsigned __stdcall GetReturnRoute(void* data_);

	/**
	* @biref マップの移動経路情報とエネミーの巡回ルートの読み込み関数
	*/
	bool LoadResouces();

	/**
	* @biref マップの移動経路情報からマップのグラフを作成する関数
	*/
	void CreateGraph();

private:

	/**
	* @biref コンストラクタ
	*/
	Navigator();

	/**
	* @biref デストラクタ
	*/
	~Navigator();

	/**
	* @biref セルがグラフ内に存在するか確認する関数
	* @return グラフ内にあればtrue, ない場合はfalse
	* @param[in] row_  セルのrow
	* @param[in] column_ セルのcolumn
	* @param[in] width_ グラフのcolumnの最大値
	* @param[in] height_ グラフのrowの最大値
	*/
	bool IsCellInRange(int row_, int column_, int width_, int height_);

	/**
	* @biref セルが同じものか判定する関数
	* @return セルが同じであればtrue, そうでないならfalse
	* @param[in] a_ 判定するセル
	* @param[in] b_ 判定するセル
	*/
	static bool IsEqualCell(const Cell& a_, const Cell& b_);

	/**
	* @biref ヒューリスティックコストを算出する関数
	* @return 算出されたコスト（ユークリッド距離）
	* @param[in] node_ 現在のノード
	* @param[in] goal_ 終点のノード
	*/
	static float CalculateHeruristicCost(const Node* node_, const Node* goal_);

	/**
	* @biref 探索候補のノードをオープンリストに追加する処理
	* @param[in] open_ オープンリスト
	* @param[in] close_ クローズリスト
	* @param[in] current_ 探索中のルート
	* @param[in] add_ 追加予定のノード
	* @param[in] cost_ 追加予定のノードのヒューリスティックコスト
	*/
	static void AddRoute(std::list<std::unique_ptr<Route>>& open_, std::list<std::unique_ptr<Route>>& close_, std::unique_ptr<Route>& current_, Node* add_, float cost_);

private:
	std::vector<std::vector<std::string>> m_Route;	//!< エネミーの巡回ルート
	static std::vector<std::vector<std::string>> m_MovingPath; //!< マップの移動経路情報
	static std::vector<std::vector<Node>> m_Graph; //!< 移動経路をグラフにしたもの
};

#endif // !NAVIGATIONAI_H_
