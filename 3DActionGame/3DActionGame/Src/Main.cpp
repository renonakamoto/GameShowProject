#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Engine/Engine.h"
#include "Scene/SceneManager.h"
#include "GameManager/GameManager.h"

#pragma comment(lib, "winmm.lib")

// フレームレート
#define FPS 144.0

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

	// 周波数を取得
	LARGE_INTEGER time_freq;
	QueryPerformanceFrequency(&time_freq);

	// 1フレームのかける秒数
	const double FRAME_TIME = 1.0 / FPS;
	double frame_time = 0.0;

	// 計測開始時の時間
	LARGE_INTEGER time_start;

	// 計測時間終了時の時間
	LARGE_INTEGER time_end;
	
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
			// 計測開始時間を取得
			QueryPerformanceCounter(&time_start);


			// シーンの更新
			SceneManager::GetInstance()->Update();
			
			// シーンの描画
			SceneManager::GetInstance()->Draw();


			// 計測終了時間を取得
			QueryPerformanceCounter(&time_end);
			// 終了時間から開始時間引いたものを周波数で割り経過時間を出す
			frame_time = static_cast<double>(time_end.QuadPart - time_start.QuadPart) / static_cast<double>(time_freq.QuadPart);
			// もし処理時間が1フレームにかける時間よりも少なかった場合
			if (frame_time < FRAME_TIME)
			{
				// 1フレームにかける時間から1フレームにかかった時間を引いて待機する秒数を算出
				// 算出した秒数に1000をかけてmsに変換
				DWORD sleep_time = static_cast<DWORD>((FRAME_TIME - frame_time) * 1000.0);

				// 待機する
				Sleep(sleep_time);
			}
		}
	}
	
	// Enigineの解放
	Engine::GetInstance()->Release();

	return 0;
}