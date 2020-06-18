#ifndef CONFIGSCENE_H_
#define CONFIGSCENE_H_

#include "Scene.h"
#include "../UI/ConfigUI/ConfigUI.h"

class ConfigScene : public Scene
{
public:
	ConfigScene(SceneChanger* sceneChanger_);
	virtual ~ConfigScene();

	void Update() override;
	void Draw()   override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);

	ConfigUI* m_ConfigUI;
};

#endif // !CONFIGSCENE_H_
