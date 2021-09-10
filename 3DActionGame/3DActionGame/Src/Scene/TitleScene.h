#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "Scene.h"

/**
* @brief タイトルシーンクラス
*/
class TitleScene : public Scene
{
public:
	/**
	* @biref コンストラクタ
	* @param[in] sceneChanger_ シーン変更のためのインターフェイス(SceneManager)のポインタ
	*/
	TitleScene(SceneChanger* sceneChanger_);

	/**
	* @biref デストラクタ
	*/
	virtual ~TitleScene();

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
	
	/**
	* @fn void ChangeGameScene()
	* @brief ゲームシーンに遷移するための関数
	*/
	void ChangeGameScene();

	/**
	* @fn void ChangeControlScene()
	* @brief 操作説明シーンに遷移するための関数
	*/
	void ChangeControlScene();
};

#endif // !TITLESCENE_H_
