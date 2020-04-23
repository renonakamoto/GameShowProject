#ifndef OPENINGSCENE_H_
#define OPENINGSCENE_H_

#include "Scene.h"

class OpeningScene : public Scene
{
public:
	OpeningScene(SceneChanger* sceneChanger_);
	virtual ~OpeningScene();

	void Update() override;
	void Draw() override;

private:
	void Load() override;
	void Main() override;
	static DWORD WINAPI LoadResources(LPVOID lpParam_);
};

#endif // !OPENINGSCENE_H_