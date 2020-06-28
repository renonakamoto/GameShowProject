#include "ClearScene.h"
#include "../Engine/Input/InputManager.h"

ClearScene::ClearScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
    m_GameClearUI = new GameClearUI();

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
    delete m_GameClearUI;
    m_GameClearUI = nullptr;

    THE_TEXTUREMANAGER->Release("assets/UI/gameclear/clear01.png");
    THE_TEXTUREMANAGER->Release("assets/UI/gameclear/clear02.png");
}

void ClearScene::Load()
{
    THE_TEXTUREMANAGER->Load("assets/UI/gameclear/clear01.png");
    THE_TEXTUREMANAGER->Load("assets/UI/gameclear/clear02.png");

    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI ClearScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void ClearScene::Main()
{
    m_GameClearUI->Update();

    for (int i = 0; i < static_cast<int>(KeyInfo::Max_Key_Info); ++i)
    {
        if (THE_INPUTMANAGER->GetKeyDown(static_cast<KeyInfo>(i)))
        {
            m_SceneChanger->ChangeScene(SceneID::Tilte);
        }
    }
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
    m_GameClearUI->Draw();
}