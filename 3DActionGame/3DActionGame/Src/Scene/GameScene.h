#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "Scene.h"
#include "../Engine/Model/FbxModel/FbxModel.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Objects/Sprite/Sprite.h"

/**
* @brief ゲームシーンクラス
*/
class GameScene : public Scene
{
public:
	GameScene(SceneChanger* sceneChanger_);

	/**
	* @biref デストラクタ
	*/
	virtual ~GameScene();

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
	* @details リソースの読み込みが終了していたらシーンのステップを進める
	*/
	void Load() override;

	/**
	* @fn void Main()
	* @brief メイン処理関数
	* @details シーンのメイン処理をここで行う
	*/
	void Main() override;

	/**
	* @fn static DWORD WINAPI LoadResources(LPVOID lpParam_)
	* @brief リソース読み込み関数
	* @param[in] lpParam_ リソース読み込み時に必要な引数
	* @details シーンに必要なリソースを読み込む
	*/
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

private:
	Sprite m_OffScreenSprite;	//! オフスクリーンのバッファ情報を持っているスプライト

};

#endif // !GAMESCENE_H_
