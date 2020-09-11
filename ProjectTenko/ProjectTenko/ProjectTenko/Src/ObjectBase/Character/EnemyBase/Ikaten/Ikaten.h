#ifndef IKATEN_H_
#define IKATEN_H_

#include "../EnemyBase.h"

enum class IkatenMotionList : unsigned char
{
	Attack,
	Wait,
};

class Ikaten : public Enemybase
{
public:
	Ikaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_);

	~Ikaten() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	/**
	* @biref �����Ԃ̈ړ������֐�
	*/
	void Patrol() override;

	/**
	* @biref ����o�H�ɕ��A���邽�߂̌o�H�T���֐�
	*/
	void Attack() override;

	bool IsPlayerRanged();

private:
	IkatenMotionList			m_CurrentMotion;	//!< ���݂̃��[�V����
	FbxMotion<IkatenMotionList>	m_Motion;			//!< ���[�V�������X�g

	int m_FrameCounter;
	float m_AttackRange;
};

#endif