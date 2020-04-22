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

	friend MySingletonTemplate::SingletonTemplate<InputManager>;

public:
	/**
	* @brief Input�@�\�̏������֐�
	* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s���܂�
	* @return ���������ʁA�����̏ꍇ��true
	* @param[in] hInstance_	�C���X�^���X�n���h��
	* @param[in] hWindow_	�E�B���h�E�n���h��
	*/
	bool Init(HINSTANCE hInstance_, HWND hWindow_);

	/**
	* @brief Input�@�\�̏I���֐�
	* Input�@�\���I�������܂�
	*/
	void Release();

	/**
	* @biref ���͏��̍X�V
	* �}�E�X�A�L�[�{�[�h�A�Q�[���p�b�h�̓��͏��̍X�V���s���܂�
	*/
	void Update();


//!< �ȉ��}�E�X�֘A�̊֐�
	/***
	* @biref �}�E�X��������Ă��邩�̏��擾�֐�
	* @param[in] button_ �}�E�X�̃{�^���̎��
	*/
	bool GetMouse(MouseButton button_)const;

	/***
	* @biref �}�E�X�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �}�E�X�̃{�^���̎��
	*/
	bool GetMouseDown(MouseButton button_)const;

	/***
	* @biref �}�E�X�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �}�E�X�̃{�^���̎��
	*/
	bool GetMouseUp(MouseButton button_)const;

	/***
	* @biref �}�E�X���W�̎擾�֐�
	*/
	POINT GetMousePos()const;


//!< �ȉ��L�[�{�[�h�֘A�̊֐�
	/***
	* @biref �L�[��������Ă��邩�̏��擾�֐�
	* @param[in] button_ �L�[�̎��
	*/
	bool GetKey(KeyInfo key_)const;

	/***
	* @biref �L�[�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �L�[�̎��
	*/
	bool GetKeyDown(KeyInfo key_)const;

	/***
	* @biref �L�[�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �L�[�̎��
	*/
	bool GetKeyUp(KeyInfo key_)const;

//!< �ȉ��Q�[���p�b�h�֘A�̊֐�
	/**
	* @brief �{�^����������Ă��邩�̏��擾�֐�
	* @param[in] num_ �R���g���[���[�̔ԍ�
	* @param[in] btn_ �{�^���̎��
	*/
	bool GetButton(GamePadButton btn_)const;

	/**
	* @brief �{�^����������Ă��u�Ԃ��̏��擾�֐�
	* @param[in] num_ �R���g���[���[�̔ԍ�
	* @param[in] btn_ �{�^���̎��
	*/
	bool GetButtonDown(GamePadButton btn_)const;

	/**
	* @brief �{�^���������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] num_ �R���g���[���[�̔ԍ�
	* @param[in] btn_ �{�^���̎��
	*/
	bool GetButtonUp(GamePadButton btn_)const;

//!< �ȉ����z�R���g���[���[�p
	int GetInputState(InputInfo id_)const;

private:
	/**
	* @biref �R���X�g���N�^
	*/
	InputManager();

	/**
	* @biref �f�X�g���N�^
	*/
	~InputManager() { }

	/**
	* @brief �L�[�{�[�h�p�̃f�o�C�X�̐���
	* �L�[�{�[�h�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	*/
	bool CreateKeyDevice(HWND hWindow_);

	/**
	* @brief �L�[�{�[�h�̓��͏��X�V�֐�
	*/
	void UpdateKeyState();

	/**
	* @brief �}�E�X�p�̃f�o�C�X�̐���
	* �}�E�X�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief �}�E�X�̓��͏��X�V�֐�
	*/
	void UpdateMouseState();

	/**
	* @brief �Q�[���p�b�h�p�̃f�o�C�X����
	* �Q�[���p�b�h�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	* @param[in] hWindow_ �E�B���h�E�n���h��
	*/
	bool CreateGamePadDevice(HWND hWindow_);

	/**
	* @brief �Q�[���p�b�h�̓��͏��X�V�֐�
	*/
	void UpdateGamePadState();

	/**
	* @biref �Q�[���p�b�h�񋓗p�֐�
	* �Q�[���p�b�h�̏������Ŏg�p����񋓊֐��ł�
	*/
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE pdevins, LPVOID pContext);

	/**
	* @biref �Q�[���p�b�h�̃v���p�e�B�ݒ�֐�
	* �Q�[���p�b�h�̏������Ŏg�p����A�v���p�e�B�ݒ�p�̊֐��ł�
	*/
	static bool SetGamePadPropaty(LPDIRECTINPUTDEVICE8 device);

	/**
	* @biref �Q�[���p�b�h�̍ċN���֐�
	* �f�o�C�X���X�g�̍ۂɃQ�[���p�b�h�̍ċN�����s���֐��ł�
	*/
	bool RestartGamePad(LPDIRECTINPUTDEVICE8 device);

private:
	static const int m_Unresponsive_Range = 200;


	static LPDIRECTINPUT8 m_Interface;		//!< DirectInput8�̃C���^�[�t�F�C�X
	LPDIRECTINPUTDEVICE8 m_KeyDevice;		//!< �L�[�{�[�h�p�f�o�C�X
	LPDIRECTINPUTDEVICE8 m_MouseDevice;		//!< �}�E�X�p�̃f�o�C�X
	LPDIRECTINPUTDEVICE8 m_GamePadDevice;	//!< �Q�[���p�b�h�p�̃f�o�C�X

	InputState m_KeyState[static_cast<int>(KeyInfo::Max_Key_Info)];			//!< �L�[�{�[�h���͏��
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
	};																		//!< �L�[�{�[�h���蓖�ď��

	InputState m_MouseState[3];		//!< �}�E�X���͏��
	InputState m_GamePadState[static_cast<int>(GamePadButton::MAX_INFO)];		//!< �Q�[���p�b�h���͏��

	int m_InputState[static_cast<int>(InputInfo::Max_ID)];				//!< ���͏��
};

typedef MySingletonTemplate::SingletonTemplate<InputManager> InputMA;
#define THE_INPUTMANAGER InputMA::GetInstance()

#endif INPUT_MANAGER