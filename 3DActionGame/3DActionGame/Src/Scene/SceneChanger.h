#ifndef SCENECHANGER_H_
#define SCENECHANGER_H_

#include "SceneDefinition.h"
#include "Scene.h"

class Scene;

class SceneChanger
{
public:
	/**
	* @biref コンストラクタ
	*/
	SceneChanger() = default;
	
	/**
	* @biref デストラクタ
	*/
	virtual ~SceneChanger() = default;
	
	/**
	* @biref シーン変更関数
	* スタックをクリアして指定したシーンを生成します
	* @param[in] scene_ 変更する次のシーン
	*/
	virtual void ChangeScene(SceneID id_) = 0;

	/**
	* @biref シーン追加関数
	* スタックをクリアせずに指定したシーンを生成します
	* @param[in] scene_ 追加するシーン
	*/
	virtual void PushScene(SceneID id_) = 0;

	/**
	* @biref シーン削除関数
	* 現在のシーンを削除します
	*/
	virtual void PopScene() = 0;
};

#endif // !SCENECHANGER_H_