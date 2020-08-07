#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#include "State.h"
#include <vector>
#include <memory>

enum class StateType
{
	Move,
	Patrol,
	Turn,
	Chase,
	Return,
	Thinking,
	Attack
};

class StateManager
{
public:
	static StateManager* GetInstance()
	{
		static StateManager instance;
		return &instance;
	}

	State* GetState(StateType type_) const;

private:
	StateManager();

	~StateManager();

private:
	std::vector<std::unique_ptr<State>> m_StateList;

};

#endif // !STATEMANAGER_H_
