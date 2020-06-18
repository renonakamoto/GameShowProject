#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../../Camera/Camera.h"
#include "../Character.h"

enum class PlayerMotionList : unsigned char
{
	Wait,			//! 待機
	Walk,			//! 歩く
	Squat,			//! しゃがむ
	Squat_Wait,		//! しゃがむ待機
	Squat_Walk,		//! しゃがみ歩き
	Stand_Up,		//! 立ち上がる
	Scared,			//! おびえる
	Squat_Scared,	//! おびえてしゃがむ
};

class Player : public Character
{
public:
	Player(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Player() {}

	virtual void Update() override;
	virtual void Draw()   override;
	
	void Move();
	void Motion();

	void State();

private:
	float m_WalkSpeed;						//! 立ってる状態でのスピード
	float m_SquatWalkSpeed;					//! しゃがんでる状態でのスピード
	PlayerMotionList m_CrrentMotion;		//! 現在のモーション
	FbxMotion<PlayerMotionList> m_Motion;	//! モーションクラス

	bool m_IsSquat;

	D3DXVECTOR3 m_OldPos;					//! 前の座標
	
};

#endif