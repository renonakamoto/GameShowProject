#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Utility/SingletonTemplate.h"
#include "../../Src/ObjectBase/ObjectBase.h"
#include "../Camera/Camera.h"
#include <vector>
#include <iostream>
#include <memory>

class Objectmanager
{

	friend MySingletonTemplate::SingletonTemplate<Objectmanager>;
public:
	
	void Update();
	void Draw();

	Camera* GetCameraInstance()const {
		if (m_Camera) { return nullptr; }
		return m_Camera;
	}

	void AllRelease();

private:
	Objectmanager();
	~Objectmanager();

	std::vector<ObjectBase*> m_Object;

	Camera* m_Camera;

};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif