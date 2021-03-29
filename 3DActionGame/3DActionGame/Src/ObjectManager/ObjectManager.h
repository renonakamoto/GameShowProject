#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <vector>
#include "ObjectBase.h"


class ObjectManager
{
public:

	void Update();
	void Draw();

	void Register(ObjectBase* object_);
	void Release();

private:
	std::vector<ObjectBase*> m_Objects;
	
};

#endif