#ifndef POSEUI_H_
#define POSEUI_H_

#include "../UI.h"

/**
* @brief �|�[�YUI���X�g
*/
enum class PAUSE_UI_LIST
{
	PAUSE_UI_BACKGROUND,	//! �w�i
	PAUSE_UI_RETURN_GAME,	//! �Q�[���߂�
	PAUSE_UI_RETURN_TITLE,	//! �^�C�g���ɖ߂�
	PAUSE_UI_SETTING,		//! �ݒ�

	PAUSE_UI_MAX,			//! UI�̐�
};

/**
* @brief �|�[�YUI�N���X
*/
class PauseUI : public UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	PauseUI();

	/**
	* @brief �f�X�g���N�^
	*/
	~PauseUI();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Draw();

	/**
	* @brief �I�����ꂽ���ǂ���
	* @param[in] id_ UI��ID
	* @return bool true: �I�����ꂽ false: �I������Ă��Ȃ�
	*/
	bool IsSelect(PAUSE_UI_LIST id_);

private:
	UI_PARAMETER m_PoseUIList[static_cast<int>(PAUSE_UI_LIST::PAUSE_UI_MAX)];	//! PoseUiList

};

#endif