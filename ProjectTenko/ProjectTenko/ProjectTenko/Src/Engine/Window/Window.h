#ifndef WINDOW_H_
#define WINDOW_H_

#include "../../Utility/SingletonTemplate.h"
#include <Windows.h>

/**
* @namespace MyWindow
* @brief ウィンドウ作成クラスの名前空間
*/
namespace MyWindow
{
	/**
	* @brief ウィンドウ作成クラス
	* @details 詳細なクラスの説明
	*/
	class Window
	{

		friend MySingletonTemplate::SingletonTemplate<Window>;
	public:

		bool Init(HINSTANCE hInstance_, const char* pName_, int width_, int height_);

		const HWND GetWindowHandle()const { return m_HWnd; }

		const int GetWindowWidth()const { return m_Width; }

		const int GetWindowHeight()const { return m_Height; }

	private:

		Window() :
			m_HWnd(nullptr),
			m_Width(0),
			m_Height(0)
		{}

		~Window() {}


		//! ウィンドウハンドル
		HWND m_HWnd;
		//! ウィンドウの横幅
		int  m_Width;
		//! ウィンドウの縦幅
		int  m_Height;

	};
}

#endif