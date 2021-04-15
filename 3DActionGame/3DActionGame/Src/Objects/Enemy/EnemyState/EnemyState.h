#ifndef ENEMY_STATE_H_
#define ENEMY_STATE_H_

class Enemy;

class EnemyState
{
public:
	EnemyState()
	{}

	~EnemyState()
	{}

	virtual EnemyState* CheckState(Enemy* enemy_) = 0;
	virtual void Update(Enemy* enemy_) = 0;

	virtual void Enter(Enemy* enemy_) = 0;

};

#endif