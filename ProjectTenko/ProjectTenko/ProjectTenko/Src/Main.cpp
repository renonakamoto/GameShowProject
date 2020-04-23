#include "Utility/SingletonTemplate.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/DirectGraphics.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Fbx/FbxManager.h"
#include "Manager/ObjectManager.h"

int APIENTRY WinMain(HINSTANCE hInstance_,
	HINSTANCE hPrevInstance_,
	LPSTR     lpCmpLine_,
	INT       nCmdShow_)
{
	//! エンジンインスタンス生成
	Window::Create();
	DirectGraphics::Create();
	InputMA::Create();
	FbxMeshManager::Create();


	//! エンジン初期化
	if (THE_WINDOW->Init(hInstance_, "Tenko In Tempurand", 1920, 1080) == false)
	{
		return -1;
	}

	if (THE_GRAPHICS->Init(THE_WINDOW->GetWindowHandle(), 1920, 1080, false) == false)
	{
		return -2;
	}

	if (THE_INPUTMANAGER->Init(hInstance_, THE_WINDOW->GetWindowHandle()))
	{
		return -3;
	}

	ObjectManager::Create();

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

			THE_OBJECTMANAGER->Update();
			
			THE_GRAPHICS->StartDraw();

			THE_OBJECTMANAGER->Draw();

			THE_GRAPHICS->EndDraw();
		}
	}

	Window::Destory();
	DirectGraphics::Destory();
	InputMA::Destory();
	FbxMeshManager::Destory();
	ObjectManager::Destory();
	return 1;
}