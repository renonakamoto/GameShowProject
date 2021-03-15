#include "Engine/Window.h"
#include "Engine/DirectGraphics.h"
#include "Engine/InputManager.h"
#include "Engine/SoundManager.h"
#include "Engine/MeshModel/FbxModel/FbxMesh.h"

#pragma comment(lib, "winmm.lib")


DirectX::XMFLOAT3 pos(0.f, -0.f, 0.f);
DirectX::XMFLOAT3 scale(1.0f, 1.f, 1.f);
DirectX::XMFLOAT3 degree(0.0f, 180.f, 0.0f);


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

	FbxModel* model;
	model = new FbxModel();
	if (model->Load(
		"Res/Models/Ekard.fbx",
		DirectGraphics::GetInstance()->GetDevice(),
		DirectGraphics::GetInstance()->GetVertexShader()) == false)
	{
		return -3;
	}
	model->LoadMotion("Run", "Res/Models/Ekard_Run_01.fbx");
	model->Play("Run");

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
			// 入力の更新
			InputManager::GetInstance()->Update();

			static int anim_count = 0;
			anim_count++;
			if (anim_count % 30 == 0)
			{
				model->Animate();
			}


			// 描画開始
			DirectGraphics::GetInstance()->StartRendering();

			model->Render(DirectGraphics::GetInstance(), pos, scale, degree);

			// 描画終了
			DirectGraphics::GetInstance()->FinishRendering();

		}
	}

	
	/*
		解放
	*/
	DirectGraphics::GetInstance()->Release();
	InputManager::GetInstance()->Release();

	return 0;
}