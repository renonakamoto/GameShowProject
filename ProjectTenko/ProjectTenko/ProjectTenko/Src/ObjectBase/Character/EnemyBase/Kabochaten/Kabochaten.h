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

protected:

private:
	KabochaMotionList		     m_CrrentMotion;
	FbxMotion<KabochaMotionList> m_Motion;

};

#endif