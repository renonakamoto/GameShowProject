#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneChanger* sceneChanger_);
	virtual ~TitleScene();

	void Update() override;
	void Draw() override;

private:
	DWORD WINAPI LoadResources(LPVOID lpParam_) override;
	void Main() override;
	void Load() override;
};

#endif // !TITLESCENE_H_
