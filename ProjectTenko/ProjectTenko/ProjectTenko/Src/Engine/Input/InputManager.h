/*

*/


#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <dinput.h>
#include <vector>
#include "..//..//Utility/SingletonTemplate.h"

enum class InputState
{
	Not_Push,
	Release,
	PushDown,
	Push,
};

enum class MouseButton
{
	Left,
	Right,
	Center,
	Max_Mouse_Btn
};

enum class KeyInfo
{
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_Up,
	Key_Down,
	Key_Right,
	Key_Left,
	Key_Return,
	Key_ESC,
	Key_Space,
	Max_Key_Info
};

enum class GamePadButton
{
	Btn_1,
	Btn_2,
	Btn_3,
	Btn_4,
	Btn_5,
	Btn_6,
	Btn_7,
	Btn_8,
	Btn_9,
	Btn_10,
	Stc_lLeft,
	Stc_lRight,
	Stc_lUp,
	Stc_lDown,
	Stc_rLeft,
	Stc_rRight,
	Stc_rUp,
	Stc_rDown,
	Arw_Left,
	Arw_Right,
	Arw_Up,
	Arw_Down,
	MAX_INFO,

};

enum class InputInfo
{
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_Up,
	Key_Down,
	Key_Right,
	Key_Left,
	Key_Return,
	Key_ESC,
	Key_Space,
	Mouse_Left,
	Mouse_Right,
	Mouse_Wheel,
	Pad_1,
	Pad_2,
	Pad_3,
	Pad_4,
	Pad_5,
	Pad_6,
	Pad_7,
	Pad_8,
	Pad_9,
	Pad_10,
	Pad_lX,
	Pad_lY,
	Pad_rX,
	Pad_rY,
	Pad_POV,
	Max_ID,
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


//!< 以下マウス関連の関数
	/***
	* @biref マウスが押されているかの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouse(MouseButton button_)const;

	/***
	* @biref マウスが押された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseDown(MouseButton button_)const;

	/***
	* @biref マウスが離された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseUp(MouseButton button_)const;

	/***
	* @biref マウス座標の取得関数
	*/
	POINT GetMousePos()const;


//!< 以下キーボード関連の関数
	/***
	* @biref キーが押されているかの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKey(KeyInfo key_)const;

	/***
	* @biref キーが押された瞬間かの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKeyDown(KeyInfo key_)const;

	/***
	* @biref キーが離された瞬間かの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKeyUp(KeyInfo key_)const;

//!< 以下ゲームパッド関連の関数
	/**
	* @brief ボタンが押されているかの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButton(int num_, GamePadButton btn_)const;

	/**
	* @brief ボタンが押されてた瞬間かの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButtonDown(int num_, GamePadButton btn_)const;

	/**
	* @brief ボタンが離された瞬間かの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButtonUp(int num_, GamePadButton btn_)const;

//!< 以下仮想コントローラー用
	int GetInputState(InputInfo id_)const;

private:
	/**
	* @brief キーボード用のデバイスの生成
	* キーボード用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateKeyDevice(HWND hWindow_);

	/**
	* @brief キーボードの入力情報更新関数
	*/
	void UpdateKeyState();

	/**
	* @brief マウス用のデバイスの生成
	* マウス用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief マウスの入力情報更新関数
	*/
	void UpdateMouseState();

	/**
	* @brief ゲームパッド用のデバイス生成
	* ゲームパッド用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	* @param[in] hWindow_ ウィンドウハンドル
	*/
	bool CreateGamePadDevice(HWND hWindow_);

	/**
	* @brief ゲームパッドの入力情報更新関数
	*/
	void UpdateGamePadState();

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

	InputState m_KeyState[static_cast<int>(KeyInfo::Max_Key_Info)];			//!< キーボード入力情報
	int m_KeyInfo[static_cast<int>(KeyInfo::Max_Key_Info)] =
	{
	DIK_A,
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z,
	DIK_UP,
	DIK_DOWN,
	DIK_RIGHT,
	DIK_LEFT,
	DIK_RETURN,
	DIK_ESCAPE,
	DIK_SPACE,
	};																		//!< キーボード割り当て情報

	InputState m_MouseState[3];		//!< マウス入力情報
	InputState m_GamePadState[m_MaxGamePadNum][static_cast<int>(GamePadButton::MAX_INFO)];		//!< ゲームパッド入力情報

	int m_InputState[static_cast<int>(InputInfo::Max_ID)];				//!< 入力情報
};


#endif INPUT_MANAGER