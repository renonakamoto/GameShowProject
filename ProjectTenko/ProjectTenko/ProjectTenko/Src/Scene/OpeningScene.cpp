#include "OpeningScene.h"

OpeningScene::OpeningScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
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

OpeningScene::~OpeningScene()
{

}

void OpeningScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI OpeningScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void OpeningScene::Main()
{

}

void OpeningScene::Update()
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

void OpeningScene::Draw()
{

}