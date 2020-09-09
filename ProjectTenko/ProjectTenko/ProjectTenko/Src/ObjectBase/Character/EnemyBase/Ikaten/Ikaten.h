#ifndef IKATEN_H_
#define IKATEN_H_

#include "../EnemyBase.h"

class Ikaten : public Enemybase
{
public:
	Ikaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_);

	~Ikaten() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:
	void Patrol() override;
	void Turn() override;
	void Chase() override;
	void Return() override;
	void Thinking() override;
	void Attack() override;

	bool IsPlayerRanged();

private:
	float m_AttackRange;
};

#endif