#include "InputManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
LPDIRECTINPUT8 InputManager::m_Interface = nullptr;

struct GamePadEnumParam
{
	LPDIRECTINPUTDEVICE8* GamePadDevList;
	int FindCount;
	HWND windowhandle;
};

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

	// カウント数が2以上になった場合列挙終了
	if (param->FindCount >= m_MaxGamePadNum)
	{
		return DIENUM_STOP;
	}

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
	param.GamePadDevList = m_GamePadDevices;
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
		if (FAILED(m_GamePadDevices[i]->Acquire()))
		{
			return false;
		}
		m_GamePadDevices[i]->Poll();
	}
	
	return true;
}

void InputManager::Release()
{
	for (int i = 0; i < m_MaxGamePadNum; i++)
	{
		if (m_GamePadDevices[i] != nullptr)
		{
			m_GamePadDevices[i]->Unacquire();
			m_GamePadDevices[i]->Release();
			m_GamePadDevices[i] = nullptr;
		}
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

}