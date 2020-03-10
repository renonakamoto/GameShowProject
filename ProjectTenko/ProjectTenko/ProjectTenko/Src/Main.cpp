#include "Engine/Window/Window.h"
#include "Utility/SingletonTemplate.h"

typedef MySingletonTemplate::SingletonTemplate<MyWindow::Window> Window;
#define THE_WINDOW Window::GetInstance()

int APIENTRY WinMain(HINSTANCE hInstance_,
	HINSTANCE hPrevInstance_,
	LPSTR     lpCmpLine_,
	INT       nCmdShow_)
{
	THE_WINDOW->Init(hInstance_, "Tenko In Tempurand", 1920, 1080);

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
			
		}
	}

	Window::Destory();
}