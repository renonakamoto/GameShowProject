#ifndef CLEARSCENE_H_
#define CLEARSCENE_H_

#include "Scene.h"
#include "../UI/GameClearUI/GameClearUI.h"

class ClearScene : public Scene
{
public:
	ClearScene(SceneChanger* sceneChanger_);
	virtual ~ClearScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

	GameClearUI* m_GameClearUI;
};

#endif // !CLEARSCENE_H_
