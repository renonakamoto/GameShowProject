#ifndef CLEARSCENE_H_
#define CLEARSCENE_H_

#include "Scene.h"

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
	DWORD WINAPI LoadResources(LPVOID lpParam_) override;
};

#endif // !CLEARSCENE_H_
