#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Player/Player.h"
#include "../Character.h"
#include <vector>
#include <d3dx9.h>
#include "EnemyAI/State.h"

#define ENEMY_VIEW 20.0f
#define ENEMY_VIEW_ANGLE 45.0f
#define ENEMY_ROTATE 0.026f

class State;

class Enemybase : public Character
{
public:
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

	virtual ~Enemybase() {}

	virtual void Patrol(){}
	virtual void Move() {}
	virtual void Turn() {}

	virtual void Chase(){}
	virtual void Return(){}
	virtual void Thinking(){}

	void DecideReturnPoint();

	bool CanDetectPC();

protected:
	State* m_State;			//!< 現在の状態
	std::vector<D3DXVECTOR3> m_PatrolRoute;
	D3DXVECTOR3 m_NextRoute;
	unsigned m_NextRouteNum;

	float m_Speed;
	float m_NextAngle;
	D3DXVECTOR3 m_MovingVector;
	bool m_IsClockwise;

	std::vector<D3DXVECTOR3> m_ReturnRoute;
	bool m_IsThinking;

	const ObjectBase* m_RefPlayer;		//!< プレイヤーの参照用変数

	HANDLE m_Handle;

private:
};

#endif