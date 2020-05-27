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
	* @biref コンストラクタ
	*/
	SceneManager();

	/**
	* @brief デストラクタ
	*/
	~SceneManager();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @biref 描画関数
	*/
	void Draw();

	/**
	* @biref シーン変更関数
	*/
	void ChangeScene(SceneID id_) override;

	/**
	* @biref シーン追加関数
	*/
	void PushScene(SceneID id_) override;

	/**
	* @biref シーン削除関数
	*/
	void PopScene() override;

	/**
	* @biref ゲーム終了関数
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