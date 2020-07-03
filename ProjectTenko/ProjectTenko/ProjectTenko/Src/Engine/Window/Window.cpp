#include "Window.h"

LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_)
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


bool MyWindow::Window::Init(HINSTANCE hInstance_, const char* pName_, int width_, int height_)
{
	m_Width  = width_;
	m_Height = height_;

	//! ウィンドウの設定
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WindowProc,
		0,
		0,
		hInstance_,
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),
		LoadCursor(NULL, IDC_ARROW),
		NULL,
		NULL,
		TEXT("Tenko"),
		NULL
	};

	//! ウィンドウクラスの登録
	if (!RegisterClassEx(&window_class))
	{
		MessageBox(NULL, TEXT("ウィンドウクラスの作成に失敗しました"), NULL, MB_OK);
		return false;
	}

	RECT rc = { 0,0,width_, height_ };
	AdjustWindowRect(
		&rc,
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		FALSE);

	//! 登録したクラスのウィンドウクラスを生成
	m_HWnd = CreateWindow(
		TEXT("Tenko"),
		TEXT("Tenko"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width_,
		height_,
		NULL,
		NULL,
		hInstance_,
		NULL);

	if (m_HWnd == nullptr)
	{
		MessageBox(NULL, TEXT("ウィンドウの作成に失敗しました"), NULL, MB_OK);
		return false;
	}
	
	RECT window_rect;
	RECT client_rect;

	// ウィンドウサイズとクライアント領域の取得
	if (GetWindowRect(m_HWnd, &window_rect) == false
		|| GetClientRect(m_HWnd, &client_rect) == false)
	{
		return false;
	}

	float horizon_magnification  = (float)GetSystemMetrics(SM_CXSCREEN)  / width_;
	float vertical_magnification = (float)GetSystemMetrics(SM_CYSCREEN) / height_;

	window_rect.left	/= horizon_magnification;
	window_rect.right	/= horizon_magnification;
	window_rect.bottom	/= horizon_magnification;
	window_rect.top		/= horizon_magnification;

	client_rect.left /= horizon_magnification;
	client_rect.right /= horizon_magnification;
	client_rect.bottom /= horizon_magnification;
	client_rect.top /= horizon_magnification;

	

	// フレームサイズ算出
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);
	
	// リサイズ用サイズの算出
	int resize_width  = frame_size_x + width_;
	int resize_height = frame_size_y + height_;

	// ウィンドウサイズ更新
	SetWindowPos(
		m_HWnd,
		NULL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		resize_width,
		resize_height,
		SWP_NOMOVE);	

	//! ウインドウの表示
	ShowWindow(m_HWnd, SW_SHOW);
	UpdateWindow(m_HWnd);

	return true;
}