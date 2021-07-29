#include "Window.h"

const char* Window::ClassName = "ActionGame";

LRESULT Window::WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_)
{
	switch (messageId_)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_MOUSEWHEEL:
	{
		int wheel_param = GET_WHEEL_DELTA_WPARAM(wparam_);
		// 上方向
		if (wheel_param > 0)
		{
		}
		// 下方向
		else if (wheel_param < 0)
		{
		}
	}
		break;
	default:
		return DefWindowProc(windowHandle_, messageId_, wparam_, lparam_);
		break;
	}

	return 0;
}

bool Window::Create(int windowWidth_, int windowHeight, const char* titleName_)
{
	if (EntryWindowClass() == false)
	{
		return false;
	}

	DWORD dw_style = WS_OVERLAPPEDWINDOW;

	RECT rect;
	rect.left   = 0;
	rect.top    = 0;
	rect.right  = static_cast<LONG>(windowWidth_);
	rect.bottom = static_cast<LONG>(windowHeight);

	// ウィンドウのスタイルに合わせたサイズを取得
	AdjustWindowRect(&rect, dw_style, false);

	// ウィンドウ作成
	m_WindowHandle = CreateWindow(
		Window::ClassName,
		titleName_,
		dw_style,
		CW_USEDEFAULT,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (m_WindowHandle == NULL)
	{
		return false;
	}

	m_ClientWidth = windowWidth_;
	m_ClientHeight = windowHeight;

	// Windowを真ん中に持ってくる
	SetCenterWindow(m_WindowHandle);

	return true;
}

bool Window::EntryWindowClass()
{
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),			// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,	// クラスのスタイル
		WindowProc,					// ウィンドウプロシージャ
		0,							// 補助メモリ
		0,							// 補助メモリ		
		GetModuleHandle(NULL),		// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),// カーソル画像
		NULL,						// 背景ブラシ(背景色)
		NULL,						// メニュー名
		Window::ClassName,			// クラス名
		NULL						// 小さいアイコン		
	};

	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}
	
	return true;
}

void Window::SetCenterWindow(HWND windowHandle_)
{
	int screen_width  = GetSystemMetrics(SM_CXFULLSCREEN);
	int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);

	int x = (screen_width  - m_ClientWidth)  / 2;
	int y = (screen_height - m_ClientHeight) / 2;

	// ウインドウの表示
	SetWindowPos(m_WindowHandle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	ShowWindow(m_WindowHandle, SW_SHOW);
	UpdateWindow(m_WindowHandle);
}