#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Utility/SingletonTemplate.h"
#include "../../Src/ObjectBase/ObjectBase.h"
#include "../Camera/Camera.h"
#include "../Collision/FlexibleCollision.h"
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
		if (!m_Camera) { return nullptr; }
		return m_Camera;
	}

	bool HitPlayerAndMapObject();
	bool HitPlayerAndEnemy();

	void AllRelease();

private:
	Objectmanager();
	~Objectmanager();

	std::vector<ObjectBase*> m_Object;

	std::vector<ObjectBase*> m_PlayerGroup;
	std::vector<ObjectBase*> m_EnemyGroup;
	std::vector<ObjectBase*> m_MapObjectGroup;

	Camera* m_Camera;

	FlexibleCollision m_Collision;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif