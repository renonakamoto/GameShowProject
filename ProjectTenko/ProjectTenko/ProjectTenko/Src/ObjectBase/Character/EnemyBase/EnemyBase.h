#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include <vector>
#include <d3dx9.h>

#include "../Player/Player.h"
#include "../Character.h"
#include "EnemyAI/State.h"
#include "..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//Manager/ObjectManager.h"

#define ENEMY_VIEW 300.0f
#define ENEMY_VIEW_ANGLE 100.0f
#define ENEMY_ROTATE 0.026f

class State;

class Enemybase : public Character
{
public:
	/**
	* @biref コンストラクタ
	* @param[in] pos_ 初期化時の座標
	* @param[in] player_ プレイヤーのポインタ
	* @param[in] key_ FBXのキー
	*/
	Enemybase(D3DXVECTOR3 pos_,const ObjectBase* player_ ,std::string key_):
		m_RefPlayer(player_),
		Character(pos_, key_),
		m_State(nullptr),
		m_NextRoute(0.0f, 0.0f, 0.0f),
		m_NextRouteNum(0),
		m_NextAngle(0.0f),
		m_Speed(0.35f),
		m_IsThinking(false),
		m_Handle(nullptr),
		m_IsClockwise(false)
	{}

	/**
	* @biref デストラクタ
	*/
	virtual ~Enemybase() {}

	/**
	* @biref 巡回状態の移動処理関数
	*/
	virtual void Patrol() {}
	
	/**
	* @biref 巡回中の方向転換処理関数
	*/
	virtual void Turn() {}

	/**
	* @biref プレイヤーの追跡状態処理関数
	*/
	virtual void Chase(){}

	/**
	* @biref 巡回経路に復帰する際の移動処理関数
	*/
	virtual void Return(){}
	
	/**
	* @biref 巡回経路に復帰するための経路探索関数
	*/
	virtual void Thinking(){}
	
	virtual void Attack(){}

	/**
	* @biref 座標変更関数
	*/
	virtual void Move() {}

	/**
	* @biref 最短の巡回ルートを調べる関数
	* 巡回ルートに復帰する際、最も近い巡回ルートを調べる関数
	*/
	void DecideReturnPoint();
	
	/**
	* @biref プレイヤーの探知関数
	* 視界内にプレイヤーがいるかの判定関数
	* @return プレイヤーがいる場合true, いない場合はfalse
	*/
	bool CanDetectPC();

protected:
	State* m_State;			//!< 現在の状態
	std::vector<D3DXVECTOR3> m_PatrolRoute;	//!< 巡回ルート格納コンテナ
	D3DXVECTOR3 m_NextRoute;	//!< 次の目的座標
	unsigned m_NextRouteNum;	//!< 次の巡回ルートの番号

	float m_Speed;	//!< 移動速度
	float m_NextAngle;	//!< 次の向き
	D3DXVECTOR3 m_MovingVector;	//!< 移動ベクトル
	bool m_IsClockwise;	//!< 次の向きが時計回りか否か

	NavData m_NavData;	//!< 経路探索用のデータ構造体
	bool m_IsThinking;  //!< 経路探索中か否か

	const ObjectBase* m_RefPlayer;		//!< プレイヤーの参照用変数

	HANDLE m_Handle;	//!< 経路探索処理のスレッドハンドル
private:
};

#endif