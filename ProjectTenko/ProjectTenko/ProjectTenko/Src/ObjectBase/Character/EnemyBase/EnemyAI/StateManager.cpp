#include "StateManager.h"

#include "Patrol/Patrol.h"
#include "Patrol/Turn.h"
#include "Chase.h"
#include "Return.h"
#include "Thinking.h"
#include "Attack.h"

StateManager::StateManager()
{
	m_StateList.push_back(std::make_unique<Patrol>());
	m_StateList.push_back(std::make_unique<Turn>());
	m_StateList.push_back(std::make_unique<Chase>());
	m_StateList.push_back(std::make_unique<Return>());
	m_StateList.push_back(std::make_unique<Thinking>());
	m_StateList.push_back(std::make_unique<Attack>());
}

StateManager::~StateManager()
{
	m_StateList.clear();
}

State* StateManager::GetState(StateType type_) const
{
	if (m_StateList.size() < static_cast<int>(type_))
	{
		return nullptr;
	}
	return m_StateList[static_cast<int>(type_)].get();
}
