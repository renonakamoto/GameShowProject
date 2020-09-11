#ifndef SITAKETEN_H_
#define SITAKETEN_H_

#include "../EnemyBase.h"

enum class SitaketenMotionList : unsigned char
{
	Wait,
	Walk,
	ThrowAwayPileus,
	Sprint,
	ChangeDirection,
	WearPileus,
};

class Sitaketen : public Enemybase
{
public:
	Sitaketen(D3DXVECTOR3 pos_, const ObjectBase* 
		_, std::string key_);

	~Sitaketen() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	/**
	* @biref �����Ԃ̈ړ������֐�
	*/
	void Patrol() override;

	/**
	* @biref ���񒆂̕����]�������֐�
	*/
	void Turn() override;

	/**
	* @biref �v���C���[�̒ǐՏ�ԏ����֐�
	*/
	void Chase() override;

	/**
	* @biref ����o�H�ɕ��A����ۂ̈ړ������֐�
	*/
	void Return() override;

	/**
	* @biref ����o�H�ɕ��A���邽�߂̌o�H�T���֐�
	*/
	void Thinking() override;

private:
	SitaketenMotionList m_CurrentMotion;		//!< ���݂̃��[�V����
	FbxMotion<SitaketenMotionList> m_Motion;	//!< ���[�V�������X�g
	int m_FrameCounter;
};

#endif