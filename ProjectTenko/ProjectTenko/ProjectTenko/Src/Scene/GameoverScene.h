#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "Scene.h"

class GameoverScene : public Scene
{
public:
	GameoverScene(SceneChanger* sceneChanger_);
	virtual ~GameoverScene();

	void Update() override;
	void Draw() override;
	
private:
	void Load() override;
	void Main() override;
	DWORD WINAPI LoadResources(LPVOID lpParam_) override;
};

#endif // !GAMEOVERSCENE_H_
