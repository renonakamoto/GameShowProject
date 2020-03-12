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

private:
	/**
	* @brief �L�[�{�[�h�p�̃f�o�C�X�̐���
	* �L�[�{�[�h�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	*/
	bool CreateKeyDevice(HWND hWindow_);

	/**
	* @brief �}�E�X�p�̃f�o�C�X�̐���
	* �}�E�X�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief �Q�[���p�b�h�p�̃f�o�C�X����
	* �Q�[���p�b�h�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	* @param[in] hWindow_ �E�B���h�E�n���h��
	*/
	bool CreateGamePadDevice(HWND hWindow_);

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
	bool RestartGamePad(LPDIRECTINPUTDEVICE8 device, int num);

private:
	static const int m_MaxGamePadNum = 1;
	static const int m_Unresponsive_Range = 200;


	static LPDIRECTINPUT8 m_Interface;		//!< DirectInput8�̃C���^�[�t�F�C�X
	LPDIRECTINPUTDEVICE8 m_KeyDevice;		//!< �L�[�{�[�h�p�f�o�C�X
	LPDIRECTINPUTDEVICE8 m_MouseDevice;		//!< �}�E�X�p�̃f�o�C�X
	LPDIRECTINPUTDEVICE8 m_GamePadDevices[m_MaxGamePadNum];	//!< �Q�[���p�b�h�p�̃f�o�C�X
};


#endif INPUT_MANAGER