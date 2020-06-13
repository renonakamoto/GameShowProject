#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Utility/SingletonTemplate.h"
#include "../../Src/ObjectBase/ObjectBase.h"
#include "../Camera/Camera.h"
#include "../Collision/FlexibleCollision.h"
#include "../ObjectBase/MapObject/MapDataBank.h"
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

	bool HitCameraAndObject();
	bool HitRayAndObject(const D3DXVECTOR3& origin_, const D3DXVECTOR3& delta_, float* distance_ = nullptr);

	void AllRelease();

private:
	Objectmanager();
	~Objectmanager();

	std::vector<ObjectBase*> m_Object;
	ObjectBase* m_Player;
	std::vector<ObjectBase*> m_EnemyGroup;
	std::vector<ObjectBase*> m_MapObjectGroup;

	Camera* m_Camera;

	FlexibleCollision m_Collision;
	MapDataBank m_MapDataBank;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif