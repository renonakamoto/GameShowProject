#ifndef PAUSESCENE_H_
#define PAUSESCENE_H_

#include "Scene.h"

class PauseScene : public Scene
{
public:
	PauseScene(SceneChanger* sceneChanger_);
	virtual ~PauseScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	DWORD WINAPI LoadResources(LPVOID lpParam_) override;

};

#endif // !PAUSESCENE_H_
