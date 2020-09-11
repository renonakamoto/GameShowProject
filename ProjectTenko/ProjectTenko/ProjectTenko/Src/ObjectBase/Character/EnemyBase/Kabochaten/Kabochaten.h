#ifndef KABOCHATEN_H_
#define KABOCHATEN_H_

#include "../EnemyBase.h"

enum class KabochaMotionList : unsigned char
{
	Wait,
	Walk,
	Sprint,
	LookAround,
	ChangeDirection,
};

class Kabochaten : public Enemybase
{
public:
	Kabochaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_);

	~Kabochaten() {}

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
	KabochaMotionList		     m_CrrentMotion;
	FbxMotion<KabochaMotionList> m_Motion;

};

#endif