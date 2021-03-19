﻿#include "Engine/Window.h"
#include "Engine/DirectGraphics.h"
#include "Engine/InputManager.h"
#include "Engine/SoundManager.h"
#include "Engine/MeshModel/FbxModel/FbxModel.h"
#include "Engine/MeshModel/ObjModel/ObjModel.h"
#include "Scene/SceneManager.h"

#pragma comment(lib, "winmm.lib")


int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	Window window("3DActionGame", 1280, 720);

	// ウィンドウを作成
	if (window.Create() == false)
	{
		return -1;
	}
	
	if (DirectGraphics::GetInstance()->Init() == false)
	{
		return -2;
	}

	if (InputManager::GetInstance()->Init(hInstance, window.GetWindowHandle()) == false)
	{
		return -3;
	}

	if (SoundManager::GetInstance()->Init(window.GetWindowHandle()) == false)
	{
		return -4;
	}
	SoundManager::GetInstance()->LoadSEData("Res/Sounds/button01a.wav", "button01a");
	
	while (true)
	{
		MSG msg = { 0 };

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
	
	/*
		解放
	*/
	DirectGraphics::GetInstance()->Release();
	InputManager::GetInstance()->Release();

	return 0;
}