#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "Scene.h"
#include "../UI/GameOverUI/GameOverUI.h"

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
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

	GameOverUI* m_GameOverUI;
};

#endif // !GAMEOVERSCENE_H_
