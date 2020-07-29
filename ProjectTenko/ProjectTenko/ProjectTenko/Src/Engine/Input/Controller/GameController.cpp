#include "GameController.h"
#include "..//InputManager.h"
#include <math.h>

bool GameController::Init()
{
	//m_Buttons[0] = new GameButton(InputInfo::Pad_1);
	//m_Buttons[1] = new GameButton(InputInfo::Pad_1);
	//m_Buttons[2] = new GameButton(InputInfo::Pad_2);
	//m_Buttons[3] = new GameButton(InputInfo::Pad_lY);
	//m_Buttons[4] = new GameButton(InputInfo::Pad_lY);
	//m_Buttons[5] = new GameButton(InputInfo::Pad_lX);
	//m_Buttons[6] = new GameButton(InputInfo::Pad_lX);

	return true;
}

GameController::~GameController()
{
	delete[] m_Buttons;
}

bool GameController::Update()
{
	//for (int i = 0; i < static_cast<int>(Button::MaxButtons); i++)
	//{
	//	m_Buttons[i]->Update();
	//}

	//// 左スティック処理
	//int lx = THE_INPUTMANAGER->GetInputState(InputInfo::Pad_lX);
	//int ly = THE_INPUTMANAGER->GetInputState(InputInfo::Pad_lY);
	//m_StickRad[0] = ((atan(-ly / lx) / 3.14) * 180);

	//// 右スティック処理
	//int rx = THE_INPUTMANAGER->GetInputState(InputInfo::Pad_rX);
	//int ry = THE_INPUTMANAGER->GetInputState(InputInfo::Pad_rY);
	//m_StickRad[1] = ((atan(-ry / rx) / 3.14)* 180);

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

int GameController::GetSthickRad(int stick_)
{
	return m_StickRad[stick_];
}