#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../../Camera/Camera.h"
#include "../Character.h"

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
	float m_WalkSpeed;						//! �����Ă��Ԃł̃X�s�[�h
	float m_SquatWalkSpeed;					//! ���Ⴊ��ł��Ԃł̃X�s�[�h
	PlayerMotionList m_CrrentMotion;		//! ���݂̃��[�V����
	FbxMotion<PlayerMotionList> m_Motion;	//! ���[�V�����N���X

	bool m_IsSquat;

	D3DXVECTOR3 m_OldPos;					//! �O�̍��W
	
};

#endif