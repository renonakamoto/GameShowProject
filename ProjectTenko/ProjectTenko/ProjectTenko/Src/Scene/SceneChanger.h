#ifndef SCENECHANGER_H_
#define SCENECHANGER_H_

#include "SceneDefinition.h"
#include "Scene.h"

class Scene;

class SceneChanger
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	SceneChanger() = default;
	
	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~SceneChanger() = default;
	
	/**
	* @biref �V�[���ύX�֐�
	* �X�^�b�N���N���A���Ďw�肵���V�[���𐶐����܂�
	* @param[in] scene_ �ύX���鎟�̃V�[��
	*/
	virtual void ChangeScene(SceneID id_) = 0;

	/**
	* @biref �V�[���ǉ��֐�
	* �X�^�b�N���N���A�����Ɏw�肵���V�[���𐶐����܂�
	* @param[in] scene_ �ǉ�����V�[��
	*/
	virtual void PushScene(SceneID id_) = 0;

	/**
	* @biref �V�[���폜�֐�
	* ���݂̃V�[�����폜���܂�
	*/
	virtual void PopScene() = 0;
};

#endif // !SCENECHANGER_H_