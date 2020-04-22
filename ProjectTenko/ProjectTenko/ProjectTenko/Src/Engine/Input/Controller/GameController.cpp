#include "GameController.h"

bool GameController::Init()
{
	m_Buttons[0] = new GameButton(InputInfo::Pad_1);
	m_Buttons[1] = new GameButton(InputInfo::Pad_1);
	m_Buttons[2] = new GameButton(InputInfo::Pad_2);
	m_Buttons[3] = new GameButton(InputInfo::Pad_lY);
	m_Buttons[4] = new GameButton(InputInfo::Pad_lY);
	m_Buttons[5] = new GameButton(InputInfo::Pad_lX);
	m_Buttons[6] = new GameButton(InputInfo::Pad_lX);

	return true;
}

bool GameController::Update()
{
	for (int i = 0; i < static_cast<int>(Button::MaxButtons); i++)
	{
		m_Buttons[i]->Update();
	}
	return true;
}

bool GameController::GetKeyDown(Button key_)
{
	if (m_Buttons[static_cast<int>(key_)]->GetVal() == static_cast<int>(InputState::PushDown))
	{
		return true;
	}
	return false;
}

bool GameController::GetKey(Button key_)
{
	if (m_Buttons[static_cast<int>(key_)]->GetVal() == static_cast<int>(InputState::Push))
	{
		return true;
	}
	return false;
}

bool GameController::GetKeyUp(Button key_)
{
	if (m_Buttons[static_cast<int>(key_)]->GetVal() == static_cast<int>(InputState::Release))
	{
		return true;
	}
	return false;
}