#ifndef PAUSESCENE_H_
#define PAUSESCENE_H_

#include "Scene.h"
#include "../UI/PauseUI/PauseUI.h"

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
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

	PauseUI* m_PauseUI;

};

#endif // !PAUSESCENE_H_
