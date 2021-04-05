#ifndef OBJECT_BASE_H_
#define OBJECT_BASE_H_

#include <string>

class ObjectBase
{
public:
	ObjectBase():
		m_Tag("default")
	{}

	~ObjectBase(){}

	
	virtual void Update() = 0;
	virtual void Draw() = 0;

	std::string GetTag() { return m_Tag; }

protected:
	
	virtual void Init() = 0;
	virtual void Release() = 0;

protected:
	std::string m_Tag;
};

#endif