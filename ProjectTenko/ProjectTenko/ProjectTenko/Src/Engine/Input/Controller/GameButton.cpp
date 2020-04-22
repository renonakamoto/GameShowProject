#include "GameButton.h"

GameButton::GameButton(InputInfo id_)
{
	m_ButtonID.push_back(id_);
	m_InputState = 0;
}

GameButton::~GameButton()
{
	m_ButtonID.clear();
}

bool GameButton::SetConfig(InputInfo id_)
{
	m_ButtonID.push_back(id_);
}

short GameButton::GetVal()const
{
	return m_InputState;
}

void GameButton::Update()
{
	short val = 0;
	for (auto id : m_ButtonID)
	{
		short tmp = InputManager::GetInputState(id);
		if (tmp > val)
		{
			val = tmp;
		}
	}
	m_InputState = val;
}