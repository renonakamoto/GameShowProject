/*

*/


#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <dinput.h>
#include <vector>

enum class InputState
{
	Not_Push,
	PushDown,
	Push,
	Release,
};

enum class DeviceType
{
	Keyboard,
	Mouse,
	GamePad,
};

class InputManager
{
public:
	/**
	* @brief Input機能の初期化関数
	* デバイスの入力取得に必要な初期化を行います
	* @return 初期化結果、成功の場合はtrue
	* @param[in] hInstance_	インスタンスハンドル
	* @param[in] hWindow_	ウィンドウハンドル
	*/
	bool Init(HINSTANCE hInstance_, HWND hWindow_);

	/**
	* @brief Input機能の終了関数
	* Input機能を終了させます
	*/
	void Release();

	/**
	* @biref 入力情報の更新
	* マウス、キーボード、ゲームパッドの入力情報の更新を行います
	*/
	void Update();

private:
	/**
	* @brief キーボード用のデバイスの生成
	* キーボード用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateKeyDevice(HWND hWindow_);

	/**
	* @brief マウス用のデバイスの生成
	* マウス用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief ゲームパッド用のデバイス生成
	* ゲームパッド用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	* @param[in] hWindow_ ウィンドウハンドル
	*/
	bool CreateGamePadDevice(HWND hWindow_);

	/**
	* @biref ゲームパッド列挙用関数
	* ゲームパッドの初期化で使用する列挙関数です
	*/
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE pdevins, LPVOID pContext);

	/**
	* @biref ゲームパッドのプロパティ設定関数
	* ゲームパッドの初期化で使用する、プロパティ設定用の関数です
	*/
	static bool SetGamePadPropaty(LPDIRECTINPUTDEVICE8 device);

	/**
	* @biref ゲームパッドの再起動関数
	* デバイスロストの際にゲームパッドの再起動を行う関数です
	*/
	bool RestartGamePad(LPDIRECTINPUTDEVICE8 device, int num);

private:
	static const int m_MaxGamePadNum = 1;
	static const int m_Unresponsive_Range = 200;


	static LPDIRECTINPUT8 m_Interface;		//!< DirectInput8のインターフェイス
	LPDIRECTINPUTDEVICE8 m_KeyDevice;		//!< キーボード用デバイス
	LPDIRECTINPUTDEVICE8 m_MouseDevice;		//!< マウス用のデバイス
	LPDIRECTINPUTDEVICE8 m_GamePadDevices[m_MaxGamePadNum];	//!< ゲームパッド用のデバイス
};


#endif INPUT_MANAGER