#ifndef PLAYERSTATEBASE_H_
#define PLAYERSTATEBASE_H_

class Player;

enum class PlayerMotionList : unsigned char
{
	Wait,			//! �ҋ@
	Walk,			//! ����
	Squat,			//! ���Ⴊ��
	Squat_Wait,		//! ���Ⴊ�ޑҋ@
	Squat_Walk,		//! ���Ⴊ�ݕ���
	Stand_Up,		//! �����オ��
	Scared,			//! ���т���
	Squat_Scared,	//! ���т��Ă��Ⴊ��
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