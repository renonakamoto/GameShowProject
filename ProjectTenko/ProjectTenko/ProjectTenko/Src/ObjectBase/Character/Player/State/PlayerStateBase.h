#ifndef PLAYERSTATEBASE_H_
#define PLAYERSTATEBASE_H_

class Player;

enum class PlayerMotionList : unsigned char
{
	Wait,			//! ‘Ò‹@
	Walk,			//! •à‚­
	Squat,			//! ‚µ‚á‚ª‚Ş
	Squat_Wait,		//! ‚µ‚á‚ª‚Ş‘Ò‹@
	Squat_Walk,		//! ‚µ‚á‚ª‚İ•à‚«
	Stand_Up,		//! —§‚¿ã‚ª‚é
	Scared,			//! ‚¨‚Ñ‚¦‚é
	Squat_Scared,	//! ‚¨‚Ñ‚¦‚Ä‚µ‚á‚ª‚Ş
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