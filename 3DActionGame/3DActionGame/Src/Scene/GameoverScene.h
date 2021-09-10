#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "Scene.h"

/**
* @brief ゲームオーバーシーンクラス
*/
class GameoverScene : public Scene
{
public:
	GameoverScene(SceneChanger* sceneChanger_);

	/**
	* @biref デストラクタ
	*/
	virtual ~GameoverScene();

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details シーンの更新を行う
	*/
	void Update() override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details シーンの描画を行う
	*/
	void Draw() override;
	
private:
	/**
	* @fn void Load()
	* @brief 読み込み待機関数
	* @details シーンの描画関数
	*/
	void Load() override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details シーンの描画関数
	*/
	void Main() override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details シーンの描画関数
	*/
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
};

#endif // !GAMEOVERSCENE_H_
