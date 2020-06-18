#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Player/Player.h"
#include "../Character.h"
#include <vector>

enum class EnemyState
{
	Patrol,
	Chase,
	Return,
};

class Enemybase : public Character
{
public:
	Enemybase(D3DXVECTOR3 pos_,const ObjectBase* player_ ,std::string key_):
		m_RefPlayer(player_),
		Character(pos_, key_)
	{}

	virtual ~Enemybase() {}

protected:
	virtual void Patrol(){}
	virtual void Chase(){}
	virtual void Return(){}

	virtual bool CanDetectPC() { return true; }

	EnemyState m_CurrentState;			//!< 現在の状態
	std::vector<D3DXVECTOR3> m_PatrolRoute;
	int m_NextRoute;

	D3DXVECTOR3 m_MovingVector;

	std::vector<D3DXVECTOR3> m_ReturnRoute;

	const ObjectBase* m_RefPlayer;		//!< プレイヤーの参照用変数

private:
};

#endif