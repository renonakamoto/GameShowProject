#include "DebugScene.h"
#include "../Engine/Engine.h"
#include "../GameManager/GameManager.h"

DebugScene::DebugScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
    m_ThreadHandle = CreateThread(
        nullptr,                    // セキュリティ属性
        0,                          // スタックサイズ
        this->LoadResources,        // スレッド関数
        nullptr,                    // スレッド関数に渡す引数
        0,                          // 作成オプション
        &m_dwThreadID);             // スレッドID

    m_CurrentState = SceneState::Load;
}

DebugScene::~DebugScene()
{
    TEX_MANAGER->AllRelease();
}

void DebugScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {

        // 入力モード変更
        INPUT_MANAGER->SetInputMode(InputMode::MODE_UI);
        m_CurrentState = SceneState::Main;
    }
}

void DebugScene::Update()
{
    switch (m_CurrentState)
    {
    case SceneState::Load:
        Load();
        break;
    case SceneState::Main:
        Main();
        break;
    default:
        break;
    }
}

void DebugScene::Draw()
{
    GRAPHICS->StartRendering(KindRT::RT_ON_SCREEN);
    switch (m_CurrentState)
    {
    case SceneState::Load:
        break;
    case SceneState::Main:
        TEX_MANAGER->Render("debug", { 0.f,0.f,0.f });
        break;
    default:
        break;
    }
    GRAPHICS->FinishRendering();
}

void DebugScene::Main()
{
    if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_1)) m_SceneChanger->ChangeScene(SceneID::Tilte);
    else if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_2)) m_SceneChanger->ChangeScene(SceneID::Game);
    else if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_3)) m_SceneChanger->ChangeScene(SceneID::Clear);
    else if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_4)) m_SceneChanger->ChangeScene(SceneID::Gameover);
    else if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_5)) GameManager::GetInstance()->QuitGame();
}

DWORD __stdcall DebugScene::LoadResources(LPVOID lpParam_)
{
    TEX_MANAGER->Load("Res/Textures/debug_bg.png", "debug");
	return 0;
}
