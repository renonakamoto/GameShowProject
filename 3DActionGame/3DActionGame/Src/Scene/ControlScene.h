#ifndef CONTROLSCENE_H_
#define CONTROLSCENE_H_

#include "Scene.h"

/**
* @brief ��������V�[���N���X
*/
class ControlScene : public Scene
{
public:
	ControlScene(SceneChanger* sceneChanger_);

	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~ControlScene();

	/**
	* @fn void Update()
	* @brief �X�V�֐�
	* @details �V�[���̍X�V���s��
	*/
	void Update() override;

	/**
	* @fn void Draw()
	* @brief �`��֐�
	* @details �V�[���̕`����s��
	*/
	void Draw() override;

private:
	/**
	* @fn void Load()
	* @brief �ǂݍ��ݑҋ@�֐�
	* @details ���\�[�X�̓ǂݍ��݂��I�����Ă�����V�[���̃X�e�b�v��i�߂�
	*/
	void Load() override;

	/**
	* @fn void Main()
	* @brief ���C�������֐�
	* @details �V�[���̃��C�������������ōs��
	*/
	void Main() override;

	/**
	* @fn static DWORD WINAPI LoadResources(LPVOID lpParam_)
	* @brief ���\�[�X�ǂݍ��݊֐�
	* @param[in] lpParam_ ���\�[�X�ǂݍ��ݎ��ɕK�v�Ȉ���
	* @details �V�[���ɕK�v�ȃ��\�[�X��ǂݍ���
	*/
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
};

#endif // !CLEARSCENE_H_
