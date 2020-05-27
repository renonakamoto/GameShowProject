#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

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
	Enemybase(D3DXVECTOR3 pos_, std::string key_):
		Character(pos_, key_)
	{}

	virtual ~Enemybase() {}

protected:
	virtual void Patrol();
	virtual void Chase();
	virtual void Return();

	virtual bool CanDetectPC();

	EnemyState m_CurrentState;			//!< 現在の状態
	std::vector<D3DXVECTOR3> m_PatrolRoute;
	std::vector<D3DXVECTOR3> m_ReturnRoute;

private:
};

#endif