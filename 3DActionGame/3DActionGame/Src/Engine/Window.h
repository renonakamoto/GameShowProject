#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

/**
* @brief ウィンドウの管理を行うクラス
*/
class Window
{
public:
	// ウィンドウのクラス名
	static const char* ClassName;
	
public:
	static LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_);
	
public:
	/**
	* @brief コンストラクタ
	*/
	Window(const char* title_, int width_, int height_):
		m_Title(title_),
		m_Width(width_),
		m_Height(height_)
	{}

	/**
	* @brief デストラクタ
	*/
	~Window(){}

	/**
	* @fn bool Create()
	* @brief ウィンドウ作成する関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Create();

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
	int GetClientWidth()  { return m_Width;  }

	/**
	* @fn void GetClientHeight()
	* @brief クライアントの縦幅を取得する関数
	* @return int クライアントの縦幅を返す
	*/
	int GetClientHeight() { return m_Height; }

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
	const char*  m_Title;	//! ウィンドウのタイトル名
	int m_Width;			//! ウィンドウの横幅
	int m_Height;			//! ウィンドウの縦幅
	HWND m_WindowHandle;	//! ウィンドウハンドル
};

#endif