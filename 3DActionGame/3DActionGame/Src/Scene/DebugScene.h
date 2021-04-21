#ifndef DEBUG_SCENE_H_
#define DEBUG_SCENE_H_

#include "Scene.h"

class DebugScene : public Scene
{
public:
	DebugScene(SceneChanger* sceneChanger_);
	virtual ~DebugScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
};

#endif