#ifndef GAMECLEARUI_H_
#define GAMECLEARUI_H_

#include "../UI.h"

/**
* @brief �Q�[���N���AUI���X�g
*/
enum class GAMECLEAR_UI_LIST
{
	GAMECLEAR_BACKGROUND,	//! �w�i
	GAMECLEAR_UI_RETURN,	//! �߂�

	GAMECLEAR_UI_MAX,		//! UI�̐�
};

/**
* @brief �Q�[���N���AUI�N���X
*/
class GameClearUI : public UI
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	GameClearUI();

	/**
	* @brief �f�X�g���N�^
	*/
	~GameClearUI() {}

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
	bool IsSelect(GAMECLEAR_UI_LIST id_);

private:
	UI_PARAMETER m_GameClearUIList[static_cast<int>(GAMECLEAR_UI_LIST::GAMECLEAR_UI_MAX)];	//! GameClearUiList

	bool IsLit;	//! �_�ł����邽�߂̕ϐ�
};

#endif