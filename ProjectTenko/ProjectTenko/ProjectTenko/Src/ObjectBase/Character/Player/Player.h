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
	float m_WalkSpeed;			//! 立ってる状態でのスピード
	float m_SquatWalkSpeed;		//! しゃがんでる状態でのスピード

};

#endif