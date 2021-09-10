#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <stack>
#include <memory>

#include "Scene.h"
#include "SceneChanger.h"

/**
* @brief シーン管理クラス
*/
class SceneManager : public SceneChanger
{
public:
	/**
	* @fn static SceneManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return SceneManager* インスタンスのポインタ
	*/
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
	* @fn void ChangeScene(SceneID id_)
	* @brief シーン変更関数
	* @param[in] id_ シーンID
	*/
	void ChangeScene(SceneID id_) override;

	/**
	* @fn void PushScene(SceneID id_)
	* @brief シーン追加関数
	* @param[in] id_ シーンID
	*/
	void PushScene(SceneID id_) override;

	/**
	* @fn void PopScene()
	* @brief シーン削除関数
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

	std::stack<std::shared_ptr<Scene>> m_SceneStack;		//! シーン保持変数
};

#endif // !SCENEMANAGER_H_