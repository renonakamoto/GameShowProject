#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <vector>
#include "ObjectBase.h"


class ObjectManager
{
public:
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

	void Update();
	void Draw();

	void Register(ObjectBase* object_);

	void Release();

	ObjectBase* GetObj(std::string tag_);

private:
	std::vector<ObjectBase*> m_Objects;
	
};

#endif