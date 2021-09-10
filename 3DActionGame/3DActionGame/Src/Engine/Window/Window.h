#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

/**
* @brief ウィンドウの管理を行うクラス
*/
class Window
{
public:
	//! ウィンドウのクラス名
	static const char* ClassName;
	
public:
	static LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_);
	
public:
	/**
	* @brief コンストラクタ
	*/
	Window():
		m_ClientWidth(0),
		m_ClientHeight(0),
		m_WindowHandle(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~Window(){}

	/**
	* @fn bool Create(int windowWidth_, int windowHeight_, const char* titleName_)
	* @brief ウィンドウ作成する関数
	* @param[in] windowWidth_ Windowの横幅
	* @param[in] windowHeight_ Windowの縦幅
	* @param[in] titleName_ Windowに表示させる名前
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Create(int windowWidth_, int windowHeight_, const char* titleName_);

public:
	/**
	* @fn void GetWindowHandle()
	* @brief ウィンドウハンドルを取得する関数
	* @return HWND ウィンドウハンドルを返す
	*/
	HWND GetWindowHandle() { return m_WindowHandle; }

	/**
	* @fn void GetClientWidth()
	* @brief クライアントの横幅を取得する関数
	* @return int クライアントの横幅を返す
	*/
	int GetClientWidth()  { return m_ClientWidth;  }

	/**
	* @fn void GetClientHeight()
	* @brief クライアントの縦幅を取得する関数
	* @return int クライアントの縦幅を返す
	*/
	int GetClientHeight() { return m_ClientHeight; }

private:
	/**
	* @fn bool EntryWindowClass()
	* @brief ウィンドウクラスを登録する
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool EntryWindowClass();

	/**
	* @fn void SetCenterWindow(HWND windowHandle_)
	* @brief ウィンドウを真ん中にセットする関数
	* @param[in] windowHandle_ ウィンドウハンドル
	*/
	void SetCenterWindow(HWND windowHandle_);

private:
	int m_ClientWidth;		//! クライアントの横幅
	int m_ClientHeight;		//! クライアントの縦幅
	HWND m_WindowHandle;	//! ウィンドウハンドル
};

#endif