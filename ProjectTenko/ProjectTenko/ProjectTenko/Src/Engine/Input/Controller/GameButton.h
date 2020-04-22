#ifndef GAMEBUTTON_H_
#define GAMEBUTTON_H_

#include <vector>
#include <dinput.h>
#include "../InputManager.h"

enum class Button
{
	Squat,
	Decision,
	Pause,
	Up,
	Down,
	Right,
	Left,
	MaxButtons,
};

class GameButton
{
public:
	GameButton(InputInfo id_);
	~GameButton();
	bool SetConfig(InputInfo id_);
	short GetVal()const;
	void Update();

private:
	std::vector<InputInfo> m_ButtonID;
	short m_InputState;
};

#endif GAMEBUTTON_H_