#ifndef SCENEDEFINITION_H_
#define SCENEDEFINITION_H_


enum class SceneID
{
	Tilte,
	Opening,
	Game,
	Pause,
	Config,
	Clear,
	Gameover,

	MaxSceneID,
};

enum class SceneState
{
	Init,
	Load,
	Main,
	End,
};

#endif // !SCENEDEFINITION_H_