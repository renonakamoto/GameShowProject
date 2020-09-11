#ifndef IKATEN_H_
#define IKATEN_H_

#include "../EnemyBase.h"

enum class IkatenMotionList : unsigned char
{
	Attack,
	Wait,
};

class Ikaten : public Enemybase
{
public:
	Ikaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_);

	~Ikaten() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	/**
	* @biref 巡回状態の移動処理関数
	*/
	void Patrol() override;

	/**
	* @biref 巡回経路に復帰するための経路探索関数
	*/
	void Attack() override;

	bool IsPlayerRanged();

private:
	IkatenMotionList			m_CurrentMotion;	//!< 現在のモーション
	FbxMotion<IkatenMotionList>	m_Motion;			//!< モーションリスト

	int m_FrameCounter;
	float m_AttackRange;
};

#endif