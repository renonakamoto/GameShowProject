#ifndef CONTROLSCENE_H_
#define CONTROLSCENE_H_

#include "Scene.h"

class ControlScene : public Scene
{
public:
	ControlScene(SceneChanger* sceneChanger_);
	virtual ~ControlScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
};

#endif // !CLEARSCENE_H_
