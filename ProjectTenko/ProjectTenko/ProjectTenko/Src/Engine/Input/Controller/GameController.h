#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <map>
#include "GameButton.h"

class GameController
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	GameController() : m_StickRad(), m_Buttons()
	{} 

	/**
	* @biref �f�X�g���N�^
	*/
	~GameController();

	/**
	* @biref ���z�R���g���[���[�̏�����
	* ���z�R���g���[���[�̏��������s���܂�
	* @return ���������ʁA�����̏ꍇtrue
	*/
	bool Init();

	/**
	* @brief ���z�R���g���[���[�̍X�V
	* ���z�R���g���[���[���̃{�^���̏����X�V���܂�
	* @return �X�V���ʁA��肪�������ꍇfalse
	*/
	bool Update();

	/**
	* @biref �{�^�����������u�Ԃ��̔���
	* �����Ŏw�肵���{�^�����������u�Ԃ��ǂ������肵�܂�
	* @return ���茋�ʁA�������u�ԂȂ�true
	* @param[in] key_ ���肵�����{�^��
	*/
	bool GetKeyDown(Button key_);

	/**
	* @biref �{�^���������Ă��邩�̔���
	* �����Ŏw�肵���{�^�������Ă��邩�ǂ������肵�܂�
	* @return ���茋�ʁA�����Ă���Ȃ�true
	* @param[in] key_ ���肵�����{�^��
	*/
	bool GetKey(Button key_);

	/**
	* @biref �{�^���𗣂����u�Ԃ��̔���
	* �����Ŏw�肵���{�^���𗣂����u�Ԃ��ǂ������肵�܂�
	* @return ���茋�ʁA�������u�ԂȂ�true
	* @param[in] key_ ���肵�����{�^��
	*/
	bool GetKeyUp(Button key_);

	/**
	* @biref �A�i���O�X�e�B�b�N���X���Ă�������̊p�x���擾����֐�
	* �����Ŏw�肵�����̃X�e�B�b�N���X�����Ă���������A�R���g���[���[���0�Ƃ���360�x�Œl��Ԃ��܂�
	* @return �X���Ă���p�x�A�G���[�̏ꍇ��-1��Ԃ�
	* @param[in] stick_ �X�e�B�b�N�̏��A0����
	*/
	int GetSthickRad(int stick_);

private:
	GameButton* m_Buttons[static_cast<int>(Button::MaxButtons)];
	int m_StickRad[2];
};

#endif GAMECONTROLLER_H_