#ifndef KABOCHATEN_H_
#define KABOCHATEN_H_

#include "../EnemyBase.h"

enum class KabochaMotionList : unsigned char
{
	Wait,
	Walk,
	Sprint,
	LookAround,
	ChangeDirection,
};

class Kabochaten : public Enemybase
{
public:
	Kabochaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_);

	~Kabochaten() {}

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
	KabochaMotionList		     m_CrrentMotion;
	FbxMotion<KabochaMotionList> m_Motion;

};

#endif