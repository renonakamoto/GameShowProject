#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene(SceneChanger* sceneChanger_);
	virtual ~GameScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

};

#endif // !GAMESCENE_H_
