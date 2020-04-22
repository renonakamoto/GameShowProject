#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "Scene.h"
#include "SceneChanger.h"
#include <stack>
#include <memory>

class SceneManager : public SceneChanger
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	SceneManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~SceneManager();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @biref �`��֐�
	*/
	void Draw();

	/**
	* @biref �V�[���ύX�֐�
	*/
	void ChangeScene(SceneID id_) override;

	/**
	* @biref �V�[���ǉ��֐�
	*/
	void PushScene(SceneID id_) override;

	/**
	* @biref �V�[���폜�֐�
	*/
	void PopScene() override;
private:
	std::stack<std::shared_ptr<Scene>> m_SceneStack;
};

#endif // !SCENEMANAGER_H_