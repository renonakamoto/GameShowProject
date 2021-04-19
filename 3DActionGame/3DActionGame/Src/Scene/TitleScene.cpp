#include <thread>
#include <sstream>
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Engine/Engine.h"
#include "../Engine/Texture/TextureManager.h"
#include "../Objects/2DObject/BackGround.h"
#include "../Objects/2DObject/Button.h"

void NextScene()
{
    SceneManager::GetInstance()->ChangeScene(SceneID::Game);
}

TitleScene::TitleScene(SceneChanger* sceneChanger_) : 
    Scene(sceneChanger_)
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

TitleScene::~TitleScene()
{
    ObjectManager::GetInstance()->AllRelease();
    TEX_MANAGER->AllRelease();
}

void TitleScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        ObjectManager::GetInstance()->Register(new Background("bg", DirectX::XMFLOAT3(0.f, 0.f, 1.f)));
        ObjectManager::GetInstance()->Register(new Button("start_ui", "quit_ui", NextScene, DirectX::XMFLOAT3(200.f, 360.f, 0.f)));
        ObjectManager::GetInstance()->Register(new Button("quit_ui", "start_ui", NextScene, DirectX::XMFLOAT3(800.f, 360.f, 0.f)));

        ObjectManager::GetInstance()->Init();

        INPUT->SetInputMode(InputMode::MODE_UI);
        
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI TitleScene::LoadResources(LPVOID lpParam_)
{
    TEX_MANAGER->Load("Res/Textures/title_bg.png", "bg");
    TEX_MANAGER->Load("Res/Textures/title_ui_quit.png", "quit_ui");
    TEX_MANAGER->Load("Res/Textures/title_ui_start.png", "start_ui");

    return 0;
}


void TitleScene::Main()
{
    ObjectManager::GetInstance()->Update();
}

void TitleScene::Update()
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

void TitleScene::Draw()
{
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

   
}