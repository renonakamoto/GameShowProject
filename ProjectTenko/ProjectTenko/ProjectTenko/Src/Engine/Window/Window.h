#ifndef WINDOW_H_
#define WINDOW_H_

#include "../../Utility/SingletonTemplate.h"
#include <Windows.h>
#include <d3dx9.h>

/**
* @namespace MyWindow
* @brief �E�B���h�E�쐬�N���X�̖��O���
*/
namespace MyWindow
{
	/**
	* @brief �E�B���h�E�쐬�N���X
	* @details �ڍׂȃN���X�̐���
	*/
	class Window
	{

		friend MySingletonTemplate::SingletonTemplate<Window>;
	public:

		bool Init(HINSTANCE hInstance_, const char* pName_, int width_, int height_);

		const HWND GetWindowHandle()const { return m_HWnd; }

		const int GetWindowWidth()const { return m_Width; }
		const int GetWindowHeight()const { return m_Height; }

		const D3DXVECTOR2 GetCenterWindowPos()const {
			return D3DXVECTOR2(m_Width / 2, m_Height / 2);
		}

	private:

		Window() :
			m_HWnd(nullptr),
			m_Width(0),
			m_Height(0)
		{}

		~Window() {}


		//! �E�B���h�E�n���h��
		HWND m_HWnd;
		//! �E�B���h�E�̉���
		int  m_Width;
		//! �E�B���h�E�̏c��
		int  m_Height;

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyWindow::Window> Window;
#define THE_WINDOW Window::GetInstance()

#endif