#ifndef PLAYERSTATEBASE_H_
#define PLAYERSTATEBASE_H_

class Player;

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


class PlayerStateBase
{
public:
	virtual ~PlayerStateBase(){}

	virtual void Init(Player*) = 0;

	virtual void Update(Player*) = 0;

	virtual PlayerMotionList GetType()const = 0;
};

#endif