#include "Utility/SingletonTemplate.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/DirectGraphics.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Fbx/FbxManager.h"
#include "Manager/ObjectManager.h"
#include "Engine/Font/Font.h"
#include "Scene/SceneManager.h"
#include "Manager/ConfigManager.h"
#include <crtdbg.h>

int APIENTRY WinMain(HINSTANCE hInstance_,
	HINSTANCE hPrevInstance_,
	LPSTR     lpCmpLine_,
	INT       nCmdShow_)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//! エンジンインスタンス生成
	Window::Create();
	DirectGraphics::Create();
	InputMA::Create();
	FontDevice::Create();
	FbxMeshManager::Create();
	TextureManager::Create();
	ObjectManager::Create();
	ConfigManager::Create();

#pragma region デバイス初期化
	//! ウィンドウの初期化
	if (THE_WINDOW->Init(hInstance_, "Tenko In Tempurand", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) == false)
	{
		return -1;
	}

	// グラフィックスの初期化
	if (THE_GRAPHICS->Init(THE_WINDOW->GetWindowHandle(), 1920, 1080, false) == false)
	{
		return -2;
	}

	// フォントの初期化
	if (THE_FONT->Init() == false)
	{
		return -3;
	}

	// インプットの初期化
	if (THE_INPUTMANAGER->Init(hInstance_, THE_WINDOW->GetWindowHandle()) == false)
	{
		return -4;
	}
#pragma endregion

	SingletonSceneManager::Create();


	THE_TEXTUREMANAGER->Load("assets/UI/load.png");

	//! ゲームループ開始
	while (!THE_SCENEMANAGER->IsQuit())
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
			THE_INPUTMANAGER->Update();

			THE_SCENEMANAGER->Update();
			
#pragma region ライト設定
			D3DLIGHT9 light;
			ZeroMemory(&light, sizeof(light));
			light.Type = D3DLIGHT_DIRECTIONAL;
			light.Direction.x = 0.0f;
			light.Direction.y = -0.5f;
			light.Direction.z = 0.2f;
			light.Diffuse.a = 1.0f;
			light.Diffuse.r = 0.8f;
			light.Diffuse.g = 0.8f;
			light.Diffuse.b = 0.8f;
			light.Ambient.a = 1.0f;
			light.Ambient.r = 0.5f;
			light.Ambient.g = 0.5f;
			light.Ambient.b = 0.5f;

			THE_GRAPHICS->GetD3DDevice()->SetLight(0, &light);
			THE_GRAPHICS->GetD3DDevice()->LightEnable(0, TRUE);
			THE_GRAPHICS->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
#pragma endregion

			THE_SCENEMANAGER->Draw();
		}
	}

	
	Window::Destory();
	DirectGraphics::Destory();
	FbxMeshManager::Destory();
	FontDevice::Destory();
	ObjectManager::Destory();
	TextureManager::Destory();
	InputMA::Destory();
	return 1;
}