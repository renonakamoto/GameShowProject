#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "GameButton.h"

class GameController
{
public:
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

private:
	std::vector<GameButton> m_Buttons;
};

#endif GAMECONTROLLER_H_