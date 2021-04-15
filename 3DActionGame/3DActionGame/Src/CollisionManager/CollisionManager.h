#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "../ObjectManager/Object3D.h"

class CollisionManager
{
public:
	static CollisionManager* GetInstance()
	{
		static CollisionManager instance;
		return &instance;
	}

public:
	void Register(Object3D* object_);

	bool CheckHitTest(Shape3D& shape_, Object3D* hitObject_);

	bool CheckHitObject(Shape3D& shape_, Object3D* hitObject_);
	bool CheckHitObjects(Shape3D& shape_, std::vector<Object3D*>* hitObjects_);

	void Release(Object3D* object_);

	void AllRelease();

private:
	std::vector<Object3D*> m_Collision3DList;

};

#endif