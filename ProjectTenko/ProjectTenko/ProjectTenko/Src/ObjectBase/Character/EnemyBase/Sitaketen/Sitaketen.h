#ifndef SITAKETEN_H_
#define SITAKETEN_H_

#include "../EnemyBase.h"

enum class SitaketenMotionList : unsigned char
{
	Wait,
	Walk,
	ThrowAwayPileus,
	Sprint,
	ChangeDirection,
	WearPileus,
};

class Sitaketen : public Enemybase
{
public:
	Sitaketen(D3DXVECTOR3 pos_, const ObjectBase* 
		_, std::string key_);

	~Sitaketen() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	/**
	* @biref 巡回状態の移動処理関数
	*/
	void Patrol() override;

	/**
	* @biref 巡回中の方向転換処理関数
	*/
	void Turn() override;

	/**
	* @biref プレイヤーの追跡状態処理関数
	*/
	void Chase() override;

	/**
	* @biref 巡回経路に復帰する際の移動処理関数
	*/
	void Return() override;

	/**
	* @biref 巡回経路に復帰するための経路探索関数
	*/
	void Thinking() override;

private:
	SitaketenMotionList m_CurrentMotion;		//!< 現在のモーション
	FbxMotion<SitaketenMotionList> m_Motion;	//!< モーションリスト
	int m_FrameCounter;
};

#endif