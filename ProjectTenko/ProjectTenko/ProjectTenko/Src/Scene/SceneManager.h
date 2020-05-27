#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "Scene.h"
#include "SceneChanger.h"
#include "../Utility/SingletonTemplate.h"
#include <stack>
#include <memory>

class SceneManager : public SceneChanger
{

	friend MySingletonTemplate::SingletonTemplate<SceneManager>;
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

	/**
	* @biref �Q�[���I���֐�
	*/
	void GameQuit() {
		m_IsQuit = true;
	}

	bool IsQuit() {
		return m_IsQuit;
	}
private:
	std::stack<std::shared_ptr<Scene>> m_SceneStack;

	bool m_IsQuit;
};

typedef MySingletonTemplate::SingletonTemplate<SceneManager> SingletonSceneManager;
#define THE_SCENEMANAGER SingletonSceneManager::GetInstance()

#endif // !SCENEMANAGER_H_