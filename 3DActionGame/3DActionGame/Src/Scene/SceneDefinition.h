#ifndef SCENEDEFINITION_H_
#define SCENEDEFINITION_H_

/**
* @brief シーンID
*/
enum class SceneID
{
	Tilte,		//! タイトル
	Game,		//! ゲーム
	Clear,		//! クリア
	Gameover,	//! ゲームオーバー
	Debug,		//! デバッグ
	Control,	//! 操作説明

	MaxSceneID,	//! IDの数
};

/**
* @brief シーンの状態
*/
enum class SceneState
{
	Init,	//! 初期
	Load,	//! 読み込み
	Main,	//! メイン
};

#endif // !SCENEDEFINITION_H_