#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "Scene.h"
#include "../UI/TitleUI/TitleUI.h"

class Camera;

class TitleScene : public Scene
{
public:
	TitleScene(SceneChanger* sceneChanger_);
	virtual ~TitleScene();

	void Update() override;
	void Draw() override;

private:
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
	void Main() override;
	void Load() override;

	Camera*  m_Camera;
	TitleUI* m_TitleUI;
};

#endif // !TITLESCENE_H_
