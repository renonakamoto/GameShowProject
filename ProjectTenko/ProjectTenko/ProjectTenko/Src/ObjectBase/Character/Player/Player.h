#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../../Camera/Camera.h"
#include "../Character.h"

class Player : public Character
{
public:
	Player(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Player() {}

	virtual void Update() override;
	virtual void Draw() override;

	void Move();

private:
	float m_WalkSpeed;			//! �����Ă��Ԃł̃X�s�[�h
	float m_SquatWalkSpeed;		//! ���Ⴊ��ł��Ԃł̃X�s�[�h

};

#endif