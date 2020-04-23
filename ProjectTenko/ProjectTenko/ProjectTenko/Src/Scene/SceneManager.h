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
private:
	std::stack<std::shared_ptr<Scene>> m_SceneStack;
};

#endif // !SCENEMANAGER_H_