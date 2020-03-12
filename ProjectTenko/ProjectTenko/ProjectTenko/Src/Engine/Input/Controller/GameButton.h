#ifndef GAMEBUTTON_H_
#define GAMEBUTTON_H_

#include <vector>
#include <dinput.h>

enum class Button
{
	Squat,
	Decision,
	Pause,
	Up,
	Down,
	Right,
	Left,
	Movement,
	MaxButtons,
};

enum class GameControllerID
{
	Key_A = DIK_A,
	Key_B = DIK_B,
	Key_C = DIK_C,
	Key_D = DIK_D,
	Key_E = DIK_E,
	Key_F = DIK_F,
	Key_G = DIK_G,
	Key_H = DIK_H,
	Key_I = DIK_I,
	Key_J = DIK_J,
	Key_K = DIK_K,
	Key_L = DIK_L,
	Key_M = DIK_M,
	Key_N = DIK_N,
	Key_O = DIK_O,
	Key_P = DIK_P,
	Key_Q = DIK_Q,
	Key_R = DIK_R,
	Key_S = DIK_S,
	Key_T = DIK_T,
	Key_U = DIK_U,
	Key_V = DIK_V,
	Key_W = DIK_W,
	Key_X = DIK_X,
	Key_Y = DIK_Y,
	Key_Z = DIK_Z,
	Key_Up = DIK_UP,
	Key_Down = DIK_DOWN,
	Key_Right = DIK_RIGHT,
	Key_Left = DIK_LEFT,
	Key_Return = DIK_RETURN,
	Key_ESC = DIK_ESCAPE,
	Key_Space = DIK_SPACE,
	Mouse_Left = 0x0101,
	Mouse_Right = 0x0102,
	Mouse_Wheel = 0x0103,
	Pad_0 = 0x200,
	Pad_1 = 0x201,
	Pad_2 = 0x202,
	Pad_3 = 0x203,
	Pad_4 = 0x204,
	Pad_5 = 0x205,
	Pad_6 = 0x206,
	Pad_7 = 0x207,
	Pad_8 = 0x208,
	Pad_9 = 0x209,
	Pad_StickLeft = 0x20a,
	Pad_SticlRight = 0x20b,
	Max_ID = 0xffff,
};

class GameButton
{
public:
	bool SetConfig();
	short GetVal();

private:
	std::vector<int> m_ButtonID;
	short m_InputState;
};

#endif GAMEBUTTON_H_