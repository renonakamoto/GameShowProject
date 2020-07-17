#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Player/Player.h"
#include "../Character.h"
#include <vector>
#include "EnemyAI/State.h"

class State;

class Enemybase : public Character
{
public:
	Enemybase(D3DXVECTOR3 pos_,const ObjectBase* player_ ,std::string key_):
		m_RefPlayer(player_),
		Character(pos_, key_)
	{}

	virtual ~Enemybase() {}

	virtual void Patrol(){}
	virtual void Move() {}
	virtual void Turn() {}

	virtual void Chase(){}
	virtual void Return(){}

	void DecideReturnPoint();

	virtual bool CanDetectPC() { return false; }

protected:
	State* m_State;			//!< 現在の状態
	std::vector<D3DXVECTOR3> m_PatrolRoute;
	D3DXVECTOR3 m_NextRoute;
	float m_NextAngle;
	D3DXVECTOR3 m_MovingVector;

	std::vector<D3DXVECTOR3> m_ReturnRoute;

	const ObjectBase* m_RefPlayer;		//!< プレイヤーの参照用変数

private:
};

#endif