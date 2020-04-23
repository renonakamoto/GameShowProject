#include "GameScene.h"

GameScene::GameScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
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

GameScene::~GameScene()
{

}

void GameScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI GameScene::LoadResources(LPVOID lpParam_)
{

}


void GameScene::Main()
{

}

void GameScene::Update()
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

void GameScene::Draw()
{

}