#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Engine/Engine.h"
#include "Scene/SceneManager.h"
#include "GameManager/GameManager.h"

#pragma comment(lib, "winmm.lib")

int APIENTRY WinMain(
	_In_	  HINSTANCE hInstance,
	_In_opt_  HINSTANCE hPrevInstance,
	_In_	  LPSTR     lpCmpLine,
	_In_	  INT       nCmdShow)
{
#ifdef _DEBUG
	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//　Engineの初期化
	if (Engine::GetInstance()->Init(1280, 720, "3DActionGame", hInstance) == false)
	{
		return -1;
	}
	
	while (!GameManager::GetInstance()->HasQuit())
	{
		MSG msg{ 0 };

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// シーンの更新
			SceneManager::GetInstance()->Update();
			
			// シーンの描画
			SceneManager::GetInstance()->Draw();
		}
	}
	
	// Enigineの解放
	Engine::GetInstance()->Release();

	return 0;
}