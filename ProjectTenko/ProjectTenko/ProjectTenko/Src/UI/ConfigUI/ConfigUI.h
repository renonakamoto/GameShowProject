#ifndef CONFIGUI_H_
#define CONFIGUI_H_

#include "../UI.h"

/**
* @brief �R���t�B�OUI���X�g
*/
enum class CONFIG_UI_LIST
{
	CONFIG_UI_CONFIG,					//! �R���t�B�O
	CONFIG_UI_MOUSE_NORMAL,				//! �ʏ�}�E�X
	CONFIG_UI_MOUSE_REVERSE,			//! ���]�}�E�X
	CONFIG_UI_SELECTING_MOUSE_NORMAL,	//! �I����Ԃ̒ʏ�}�E�X
	CONFIG_UI_SELECTING_MOUSE_REVERSE,	//! �I����Ԃ̔��]�}�E�X
	CONFIG_UI_RETURN,					//! �߂�

	CONFIG_UI_MAX,						//! UI�̐�
};

/**
* @brief �R���t�B�OUI�N���X
*/
class ConfigUI : public UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ConfigUI();

	/**
	* @brief �f�X�g���N�^
	*/
	~ConfigUI();

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
	bool IsSelect(CONFIG_UI_LIST id_);

private:
	UI_PARAMETER m_ConfigUIList[static_cast<int>(CONFIG_UI_LIST::CONFIG_UI_MAX)];	//! ConfigUiList

};

#endif