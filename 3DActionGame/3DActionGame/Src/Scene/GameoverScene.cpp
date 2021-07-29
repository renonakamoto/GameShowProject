#include "GameoverScene.h"
#include "SceneManager.h"
#include "../Engine/Engine.h"
#include "../Objects/2DObject/BackGround.h"

GameoverScene::GameoverScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
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

GameoverScene::~GameoverScene()
{
    ObjectManager::GetInstance()->AllRelease();
    TEX_MANAGER->AllRelease();
}

void GameoverScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        ObjectManager::GetInstance()->Register(new Background("gameover_bg"));

        ObjectManager::GetInstance()->Init();

        // 入力モード変更
        INPUT_MANAGER->SetInputMode(InputMode::MODE_UI);
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI GameoverScene::LoadResources(LPVOID lpParam_)
{
    TEX_MANAGER->Load("Res/Textures/gameover_bg.png", "gameover_bg");

    return 0;
}


void GameoverScene::Main()
{
    if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_Space))
    {
#ifdef _DEBUG
        m_SceneChanger->ChangeScene(SceneID::Debug);
#else
        m_SceneChanger->ChangeScene(SceneID::Tilte);
#endif
    }

    ObjectManager::GetInstance()->Update();
}

void GameoverScene::Update()
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

void GameoverScene::Draw()
{
    GRAPHICS->StartRendering(KindRT::RT_ON_SCREEN);
    switch (m_CurrentState)
    {
    case SceneState::Load:
        break;
    case SceneState::Main:
        ObjectManager::GetInstance()->Draw();
        break;
    default:
        break;
    }
    GRAPHICS->FinishRendering();
}