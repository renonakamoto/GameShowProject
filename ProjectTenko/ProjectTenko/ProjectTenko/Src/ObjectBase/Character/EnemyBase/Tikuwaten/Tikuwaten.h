#ifndef TIKUWATEN_H_
#define TIKUWATEN_H_

#include "../EnemyBase.h"

enum class ChikuwaMotionList : unsigned char
{
	Wait,
	Walk,
	Sprint,
	ChangeDirection,
};

class Tikuwaten : public Enemybase
{
public:
	/**
	* @biref �R���X�g���N�^
	* @param[in] pos_ ���������̍��W
	* @param[in] player_ �v���C���[�̃|�C���^
	* @param[in] key_ FBX�̃L�[���
	*/
	Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* 
		player_, std::string key_);

	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~Tikuwaten() {}

	/**
	* @biref �X�V�֐�
	*/
	virtual void Update() override;
	
	/**
	* @biref �`��֐�
	*/
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
	ChikuwaMotionList		     m_CrrentMotion;	//!< ���݂̃��[�V����
	FbxMotion<ChikuwaMotionList> m_Motion;			//!< ���[�V�������X�g
};

#endif