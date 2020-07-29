#ifndef GAMEOVERUI_H_
#define GAMEOVERUI_H_

#include "../UI.h"

/**
* @brief �Q�[���I�[�o�[UI���X�g
*/
enum class GAMEOVER_UI_LIST
{
	GAMEOVER_BACKGROUND,	//! �w�i
	GAMEOVER_UI_RETURN,		//! �߂�

	GAMEOVER_UI_MAX,		//! UI�̐�
};

/**
* @brief �Q�[���I�[�o�[UI�N���X
*/
class GameOverUI : public UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	GameOverUI();

	/**
	* @brief �f�X�g���N�^
	*/
	~GameOverUI() {}

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
	bool IsSelect(GAMEOVER_UI_LIST id_);

private:
	UI_PARAMETER m_GameOverUIList[static_cast<int>(GAMEOVER_UI_LIST::GAMEOVER_UI_MAX)];	//! GameOverUiList

};

#endif