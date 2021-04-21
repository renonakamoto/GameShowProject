#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <stack>
#include <memory>

#include "Scene.h"
#include "SceneChanger.h"

class SceneManager : public SceneChanger
{
public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

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
	/**
    * @biref コンストラクタ
    */
	SceneManager();

	/**
	* @brief デストラクタ
	*/
	~SceneManager();

	std::stack<std::shared_ptr<Scene>> m_SceneStack;		//!< シーン保持変数
};

#endif // !SCENEMANAGER_H_