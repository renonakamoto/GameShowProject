#ifndef TIKUWATEN_H_
#define TIKUWATEN_H_

#include "../EnemyBase.h"

enum class ChikuwaMotionList : unsigned char
{
	Wait,
	Walk,
	Sprint,
	ChangeDirection,
};

class Tikuwaten : public Enemybase
{
public:
	Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* 
		_, std::string key_);
	virtual ~Tikuwaten() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	void Patrol() override;
	void Move() override;
	void Turn() override;
	void Chase() override;
	void Return() override;

	bool CanDetectPC() override { return true; }

private:
	ChikuwaMotionList		     m_CrrentMotion;
	FbxMotion<ChikuwaMotionList> m_Motion;

};

#endif