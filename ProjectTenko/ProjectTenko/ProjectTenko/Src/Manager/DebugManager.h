#ifndef DEBUGMANAGER_H_
#define DEBUGMANAGER_H_

#include "../Utility/Singleton.h"

class DebugManager : public Singleton<DebugManager>
{
	friend Singleton<DebugManager>;

public:
	void Update();

	void Draw();
	
	float GetMouseSensivity() const { return m_MouseSensivity; }
	bool IsSimpleMap() const { return m_IsSimpleMap; }

private:
	DebugManager() :
		m_MouseSensivity(20.0f),
		m_IsSimpleMap(false)
	{}

	~DebugManager(){}

private:
	
	float m_MouseSensivity;
	
	bool m_IsSimpleMap;
};

#endif