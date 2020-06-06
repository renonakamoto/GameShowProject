#ifndef DEBUGSCENE_H_
#define DEBUGSCENE_H_

#include "SceneChanger.h"
#include <stack>
#include <memory>

class DebugScene : public SceneChanger
{
public:
	DebugScene(SceneChanger* sceneChanger_);
	virtual ~DebugScene();

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
	std::stack<std::unique_ptr<Scene>> m_SceneList;		//!< 自身が生成したシーン保持変数
	SceneChanger* m_SceneChanger;						//!< シーンマネージャーへのI/F
};

#endif // !DEBUGSCENE_H_
