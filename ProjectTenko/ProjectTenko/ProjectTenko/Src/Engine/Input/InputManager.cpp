#include "InputManager.h"
#include "..//Window/Window.h"
#include <d3dx9math.h>

LPDIRECTINPUT8 InputManager::m_Interface = nullptr;

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

struct GamePadEnumParam
{
	LPDIRECTINPUTDEVICE8* GamePadDevList;
	int FindCount;
	HWND windowhandle;
};

InputManager::InputManager() : m_KeyDevice(nullptr), m_MouseDevice(nullptr), m_GamePadDevice(nullptr)
{
	for (int i = 0; i < static_cast<int>(KeyInfo::Max_Key_Info); i++)
	{
		m_KeyState[i] = InputState::Not_Push;
	}

	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		m_MouseState[i] = InputState::Not_Push;
	}

	for (int i = 0; i < static_cast<int>(GamePadButton::MAX_INFO); i++)
	{
		m_GamePadState[i] = InputState::Not_Push;
	}

	for (int i = 0; i < static_cast<int>(InputInfo::Max_ID); i++)
	{
		m_InputState[i] = 0;
	}
}

bool InputManager::Init(HINSTANCE hInstance_, HWND hWindow_)
{
	// Interfaceの生成
	if (FAILED(DirectInput8Create(hInstance_,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_Interface,
		NULL)))
	{
		return false;
	}

	if (CreateKeyDevice(hWindow_) == false)
	{
		return false;
	}

	if (CreateMouseDevice(hWindow_) == false)
	{
		return false;
	}

	if (CreateGamePadDevice(hWindow_) == false)
	{
		return false;
	}

	return true;
}

bool InputManager::CreateKeyDevice(HWND hWindow_)
{
	if (FAILED(m_Interface->CreateDevice(GUID_SysKeyboard, &m_KeyDevice, nullptr)))
	{
		return false;
	}

	if (FAILED(m_KeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		m_KeyDevice->Release();
		m_KeyDevice = nullptr;
		return false;
	}

	if (FAILED(m_KeyDevice->SetCooperativeLevel(hWindow_, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		m_KeyDevice->Release();
		m_KeyDevice = nullptr;
		return false;
	}

	if (FAILED(m_KeyDevice->Acquire()))
	{
		m_KeyDevice->Release();
		m_KeyDevice = nullptr;
		return false;
	}

	return true;
}

bool InputManager::CreateMouseDevice(HWND hWindow_)
{
	if (FAILED(m_Interface->CreateDevice(GUID_SysMouse, &m_MouseDevice, nullptr)))
	{
		return false;
	}

	if (FAILED(m_MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		m_MouseDevice->Release();
		m_MouseDevice = nullptr;
		return false;
	}

	if (FAILED(m_MouseDevice->SetCooperativeLevel(hWindow_, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		m_MouseDevice->Release();
		m_MouseDevice = nullptr;
		return false;
	}

	if (FAILED(m_MouseDevice->Acquire()))
	{
		m_MouseDevice->Release();
		m_MouseDevice = nullptr;
		return false;
	}

	m_MouseDevice->Poll();

	return true;
}

BOOL CALLBACK InputManager::EnumJoysticksCallback(LPCDIDEVICEINSTANCE pDevIns, LPVOID pContext)
{
	GamePadEnumParam* param = reinterpret_cast<GamePadEnumParam*>(pContext);

	// デバイスの作成
	HRESULT hr = m_Interface->CreateDevice(
		pDevIns->guidInstance,
		&param->GamePadDevList[param->FindCount],
		nullptr);
	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// データフォーマットの設定
	hr = param->GamePadDevList[param->FindCount]->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// プロパティの設定
	if (SetGamePadPropaty(param->GamePadDevList[param->FindCount]) == false)
	{
		return DIENUM_STOP;
	}

	// 協調レベルの設定
	hr = param->GamePadDevList[param->FindCount]->SetCooperativeLevel(
		param->windowhandle,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	param->FindCount++;

	return DIENUM_STOP;
}

bool InputManager::SetGamePadPropaty(LPDIRECTINPUTDEVICE8 device)
{
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));

	// 軸を絶対値モードに設定
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X軸の値の範囲設定
	DIPROPRANGE dipran;
	ZeroMemory(&dipran, sizeof(dipran));
	dipran.diph.dwSize = sizeof(dipran);
	dipran.diph.dwHeaderSize = sizeof(dipran.diph);
	dipran.diph.dwHow = DIPH_BYOFFSET;
	dipran.diph.dwObj = DIJOFS_X;
	dipran.lMin = -1000;
	dipran.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &dipran.diph)))
	{
		return false;
	}

	// Y軸の値の範囲設定
	dipran.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &dipran.diph)))
	{
		return false;
	}

	// 上記の設定を右スティックにも設定
	dipran.diph.dwObj = DIJOFS_RX;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &dipran.diph)))
	{
		return false;
	}
	dipran.diph.dwObj = DIJOFS_RY;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &dipran.diph)))
	{
		return false;
	}

	// BufferSizeの設定
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = 1000;
	if (FAILED(device->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph)))
	{
		return false;
	}

	return true;
}

bool InputManager::CreateGamePadDevice(HWND hWindow_)
{
	GamePadEnumParam param;
	param.FindCount = 0;		// ゲームパッドの列挙数の初期化
	param.GamePadDevList = &m_GamePadDevice;
	param.windowhandle = hWindow_;


	m_Interface->EnumDevices(DI8DEVCLASS_GAMECTRL,
			EnumJoysticksCallback,
			reinterpret_cast<LPVOID>(&param),
			DIEDFL_ATTACHEDONLY);

	if (param.FindCount == 0)
	{
		return false;
	}

	// ゲームパッドの起動
	for (int i = 0; i < param.FindCount; i++)
	{
		if (FAILED(m_GamePadDevice->Acquire()))
		{
			return false;
		}
		m_GamePadDevice->Poll();
	}
	
	return true;
}

bool InputManager::RestartGamePad(LPDIRECTINPUTDEVICE8 device)
{
	if (FAILED(device->Acquire()))
	{
		for (int i = 0; i < static_cast<int>(GamePadButton::MAX_INFO); i++)
		{
			m_GamePadState[i] = InputState::Not_Push;
		}

		return false;
	}
	return true;

}

void InputManager::Release()
{

	if (m_GamePadDevice != nullptr)
	{
		m_GamePadDevice->Unacquire();
		m_GamePadDevice->Release();
		m_GamePadDevice = nullptr;
	}


	if (m_KeyDevice != nullptr)
	{
		m_KeyDevice->Unacquire();
		m_KeyDevice->Release();
		m_KeyDevice = nullptr;
	}

	if (m_MouseDevice != nullptr)
	{
		m_MouseDevice->Unacquire();
		m_MouseDevice->Release();
		m_MouseDevice = nullptr;
	}

	m_Interface->Release();
}

void InputManager::Update()
{
	UpdateKeyState();
	UpdateMouseState();
	UpdateGamePadState();
}

void InputManager::UpdateKeyState()
{
	BYTE Key[256];

	if (FAILED(m_KeyDevice->GetDeviceState(256, Key)))
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(KeyInfo::Max_Key_Info); i++)
	{
		if (Key[m_KeyInfo[i]] & 0x80)
		{
			if (m_KeyState[i] == InputState::Not_Push || m_KeyState[i] == InputState::Release)
			{
				m_KeyState[i] = InputState::PushDown;
			}
			else
			{
				m_KeyState[i] = InputState::Push;
			}
		}
		else
		{
			if (m_KeyState[i] == InputState::Push || m_KeyState[i] == InputState::PushDown)
			{
				m_KeyState[i] = InputState::Release;
			}
			else
			{
				m_KeyState[i] = InputState::Not_Push;
			}
		}

	}

	for (int i = 0; i < static_cast<int>(KeyInfo::Max_Key_Info); i++)
	{
		m_InputState[i] = static_cast<int>(m_KeyState[i]);
	}
}

void InputManager::UpdateMouseState()
{
	DIMOUSESTATE mouse;

	if (FAILED(m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse)))
	{
		m_MouseDevice->Acquire();
		m_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mouse);
	}

	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		if (mouse.rgbButtons[i] & 0x80)
		{
			if (m_MouseState[i] == InputState::Not_Push || m_MouseState[i] == InputState::Release)
			{
				m_MouseState[i] = InputState::PushDown;
			}
			else
			{
				m_MouseState[i] = InputState::Push;
			}
		}
		else
		{
			if (m_MouseState[i] == InputState::Push || m_MouseState[i] == InputState::PushDown)
			{
				m_MouseState[i] = InputState::Release;
			}
			else
			{
				m_MouseState[i] = InputState::Not_Push;
			}
		}
	}

	int key = static_cast<int>(KeyInfo::Max_Key_Info);
	
	for (int i = 0; i < static_cast<int>(MouseButton::Max_Mouse_Btn); i++)
	{
		m_InputState[i + key] = static_cast<int>(m_MouseState[i]);
	}
}

void InputManager::UpdateGamePadState()
{
	DIJOYSTATE joy;
	bool isPush[static_cast<int>(GamePadButton::MAX_INFO)] = {  };

	if (m_GamePadDevice == nullptr)
	{
			return;
	}
	
	HRESULT hr = m_GamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), &joy);
	if (FAILED(hr))
	{
		RestartGamePad(m_GamePadDevice);
	}
	
	// 左スティックの入力確認
	if (joy.lX < -m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_lLeft)] = true;
	}
	else if (joy.lX > m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_lRight)] = true;
	}
	if (joy.lY > m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_lDown)] = true;
	}
	else if (joy.lY < -m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_lUp)] = false;
	}

	m_InputState[static_cast<int>(InputInfo::Pad_lX)] = joy.lX;
	m_InputState[static_cast<int>(InputInfo::Pad_lY)] = joy.lY;


	// 右スティックの入力確認
	if (joy.lRx < -m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_rLeft)] = true;
	}
	else if (joy.lRx > m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_rRight)] = true;
	}
	if (joy.lRy > m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_rDown)] = true;
	}
	else if (joy.lRy < -m_Unresponsive_Range)
	{
		isPush[static_cast<int>(GamePadButton::Stc_rUp)] = true;
	}

	m_InputState[static_cast<int>(InputInfo::Pad_rX)] = joy.lRx;
	m_InputState[static_cast<int>(InputInfo::Pad_rY)] = joy.lRy;


	// 十字キーの入力確認
	if (joy.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((joy.rgdwPOV[0] / 100.0f));
		float x = sinf(rad);
		float y = cosf(rad);
		if (x < -0.01f)
		{
			isPush[static_cast<int>(GamePadButton::Arw_Left)] = true;
		}
		else if (x > 0.01f)
		{
			isPush[static_cast<int>(GamePadButton::Arw_Right)] = true;
		}

		if (y < -0.01f)
		{
			isPush[static_cast<int>(GamePadButton::Arw_Down)] = true;
		}
		else if (y > 0.01f)
		{
			isPush[static_cast<int>(GamePadButton::Arw_Up)] = true;
		}
	}

	m_InputState[static_cast<int>(InputInfo::Pad_POV)] = static_cast<int>(joy.rgdwPOV[0]);


	// ボタンの入力確認
	for (int j = 0; j < 10; j++)
	{
		if (joy.rgbButtons[j] == 0x80)
		{
			isPush[j] = true;
		}
	}
	
	for (int j = 0; j < static_cast<int>(GamePadButton::MAX_INFO); j++)
	{
		if (isPush[j] == true)
		{
			if (m_GamePadState[j] == InputState::Not_Push || m_GamePadState[j] == InputState::Release)
			{
				m_GamePadState[j] = InputState::PushDown;
			}
				else
				{
					m_GamePadState[j] = InputState::Push;
				}
			}
			else
			{
				if (m_GamePadState[j] == InputState::Push || m_GamePadState[j] == InputState::PushDown)
				{
					m_GamePadState[j] = InputState::Release;
				}
				else
				{
					m_GamePadState[j] = InputState::Not_Push;
				}

			}
		}

	for (int i = 0; i < static_cast<int>(GamePadButton::MAX_INFO); i++)
	{
		m_InputState[i + static_cast<int>(KeyInfo::Max_Key_Info) + static_cast<int>(MouseButton::Max_Mouse_Btn)] = static_cast<int>(m_GamePadState[i]);
	}
}

bool InputManager::GetMouse(MouseButton btn_) const
{
	if (m_MouseState[static_cast<int>(btn_)] == InputState::Push)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseDown(MouseButton btn_) const
{
	if (m_MouseState[static_cast<int>(btn_)] == InputState::PushDown)
	{
		return true;
	}
	return false;
}

bool InputManager::GetMouseUp(MouseButton btn_) const
{
	if (m_MouseState[static_cast<int>(btn_)] == InputState::Release)
	{
		return true;
	}
	return false;
}

POINT InputManager::GetMousePos() const
{
	POINT pos;
	GetCursorPos(&pos);

	ScreenToClient(THE_WINDOW->GetWindowHandle() , &pos);
}

bool InputManager::GetKey(KeyInfo key_) const
{
	if (m_KeyState[static_cast<int>(key_)] == InputState::Push)
	{
		return true;
	}
	return false;
}

bool InputManager::GetKeyDown(KeyInfo key_) const
{
	if (m_KeyState[static_cast<int>(key_)] == InputState::PushDown)
	{
		return true;
	}
	return false;
}

bool InputManager::GetKeyUp(KeyInfo key_) const
{
	if (m_KeyState[static_cast<int>(key_)] == InputState::Release)
	{
		return true;
	}
	return false;
}

bool InputManager::GetButton(GamePadButton btn_) const
{
	if (m_GamePadState[static_cast<int>(btn_)] == InputState::Push)
	{
		return true;
	}
	return false;
}

bool InputManager::GetButtonDown(GamePadButton btn_) const
{
	if (m_GamePadState[static_cast<int>(btn_)] == InputState::PushDown)
	{
		return true;
	}
	return false;
}

bool InputManager::GetButtonUp(GamePadButton btn_) const
{
	if (m_GamePadState[static_cast<int>(btn_)] == InputState::Release)
	{
		return true;
	}
	return false;
}

int InputManager::GetInputState(InputInfo id_) const
{
	return m_InputState[static_cast<int>(id_)];
}
