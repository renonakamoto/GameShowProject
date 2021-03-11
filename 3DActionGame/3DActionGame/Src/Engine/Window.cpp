#include "Window.h"

const char* Window::ClassName = "ActionGame";

LRESULT Window::WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_)
{
	switch (messageId_)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(windowHandle_, messageId_, wparam_, lparam_);
		break;
	}

	return 0;
}

bool Window::Create()
{
	if (EntryWindowClass() == false)
	{
		return false;
	}

	DWORD dw_style = (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE;

	RECT rect;
	rect.left	= 0;
	rect.top	= 0;
	rect.right  = static_cast<long>(m_Width);
	rect.bottom = static_cast<long>(m_Height);

	// ウィンドウのスタイルに合わせたサイズを取得
	AdjustWindowRect(&rect, dw_style, false);

	m_Width  = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;

	// ウィンドウ作成
	m_WindowHandle = CreateWindow(
	Window::ClassName,
	m_Title,
	dw_style,
	CW_USEDEFAULT,
	0,
	m_Width,
	m_Height,
	NULL,
	NULL,
	GetModuleHandle(NULL),
	NULL);

	if (m_WindowHandle == NULL)
	{
		return false;
	}

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
	int x, y;
	int screen_width, screen_height;
	RECT rect;

	GetWindowRect(m_WindowHandle, &rect);
	screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
	screen_height = GetSystemMetrics(SM_CYFULLSCREEN);

	x = (screen_width - (rect.right - rect.left)) / 2;
	y = (screen_height - (rect.bottom - rect.top)) / 2;

	// ウインドウの表示
	SetWindowPos(m_WindowHandle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	ShowWindow(m_WindowHandle, SW_SHOW);
	UpdateWindow(m_WindowHandle);
}