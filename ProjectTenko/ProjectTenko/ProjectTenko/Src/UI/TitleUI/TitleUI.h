#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "../UI.h"

/**
* @brief �^�C�g��UI���X�g
*/
enum class TITLE_UI_LIST
{
	TITLE_UI_TITLE,		//! �^�C�g��
	TITLE_UI_START,		//! �X�^�[�g
	TITLE_UI_EXIT,		//! �I��
	TITLE_UI_SETTING,	//! �ݒ�

	TITLE_UI_MAX,		//! UI�̐�
};

/**
* @brief TitleUI
*/
class TitleUI : public UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	TitleUI();

	/**
	* @brief �f�X�g���N�^
	*/
	~TitleUI();

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
	bool IsSelect(TITLE_UI_LIST id_);

private:

	UI_PARAMETER m_TitleUIList[static_cast<int>(TITLE_UI_LIST::TITLE_UI_MAX)];	//! TitleUiList

};

#endif