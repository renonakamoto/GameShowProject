#include "ClearScene.h"
#include "../Engine/Engine.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Objects/2DObject/BackGround.h"


ClearScene::ClearScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
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

ClearScene::~ClearScene()
{
    ObjectManager::GetInstance()->AllRelease();
    TEX_MANAGER->AllRelease();
}

void ClearScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        ObjectManager::GetInstance()->Register(new Background("gameclear_bg"));

        ObjectManager::GetInstance()->Init();

        // 入力モード変更
        INPUT_MANAGER->SetInputMode(InputMode::MODE_UI);
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI ClearScene::LoadResources(LPVOID lpParam_)
{
    TEX_MANAGER->Load("Res/Textures/gameclear_bg.png", "gameclear_bg");

    return 0;
}


void ClearScene::Main()
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

void ClearScene::Update()
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

void ClearScene::Draw()
{
    GRAPHICS->StartRendering();
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