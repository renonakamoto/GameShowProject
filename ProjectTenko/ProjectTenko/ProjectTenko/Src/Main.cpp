#include "Utility/SingletonTemplate.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/DirectGraphics.h"

typedef MySingletonTemplate::SingletonTemplate<MyWindow::Window> Window;
#define THE_WINDOW Window::GetInstance()

typedef MySingletonTemplate::SingletonTemplate<MyDirectGraphics::DirectGraphics> DirectGraphics;
#define THE_GRAPHICS DirectGraphics::GetInstance()

int APIENTRY WinMain(HINSTANCE hInstance_,
	HINSTANCE hPrevInstance_,
	LPSTR     lpCmpLine_,
	INT       nCmdShow_)
{
	//! エンジンインスタンス生成
	Window::Create();
	DirectGraphics::Create();

	//! エンジン初期化
	if (THE_WINDOW->Init(hInstance_, "Tenko In Tempurand", 1920, 1080) == false)
	{
		return -1;
	}

	if (THE_GRAPHICS->Init(THE_WINDOW->GetWindowHandle(), 1920, 1080, false) == false)
	{
		return -2;
	}

	//! ゲームループ開始
	while (true)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			
			THE_GRAPHICS->StartDraw();


			THE_GRAPHICS->EndDraw();
		}
	}

	Window::Destory();
	DirectGraphics::Destory();
	return 1;
}