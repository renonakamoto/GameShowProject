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

	//! �E�B���h�E�̐ݒ�
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

	//! �E�B���h�E�N���X�̓o�^
	if (!RegisterClassEx(&window_class))
	{
		MessageBox(NULL, TEXT("�E�B���h�E�N���X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	//! �E�B���h�E�X�^�C��
	DWORD dw_style = (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE;

	RECT rect;
	rect.left = 0;
	rect.top  = 0;
	rect.right  = m_Width;
	rect.bottom = m_Height;

	//! �E�B���h�E�N���X�̃X�^�C���ɍ��킹���K�؂ȃT�C�Y���擾����
	AdjustWindowRect(&rect, dw_style, false);

	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;

	//! �o�^�����N���X�̃E�B���h�E�N���X�𐶐�
	m_HWnd = CreateWindow(
		TEXT("Tenko"),
		TEXT("Tenko"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		0,
		0,
		width_,
		height_,
		NULL,
		NULL,
		hInstance_,
		NULL);

	if (m_HWnd == nullptr)
	{
		MessageBox(NULL, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return false;
	}

	//! �E�C���h�E�̕\��
	ShowWindow(m_HWnd, SW_SHOW);
	UpdateWindow(m_HWnd);

	return true;
}