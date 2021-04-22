#ifndef SCENEDEFINITION_H_
#define SCENEDEFINITION_H_


enum class SceneID
{
	Tilte,
	Game,
	Clear,
	Gameover,
	Debug,

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