#include <thread>
#include <sstream>
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/Texture/Texture.h"
#include "../2DObject/Title/TitleBackGround.h"
#include "../ObjectManager/UI/Button.h"

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

    m_ObjectManager = new ObjectManager();
}

TitleScene::~TitleScene()
{
    m_ObjectManager->Release();
    delete m_ObjectManager;
}

void TitleScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_ObjectManager->Register(new TitleBackground("bg", DirectX::XMFLOAT3(0.f, 0.f, 1.f)));
        m_ObjectManager->Register(new Button("start_ui", "quit_ui", NextScene, DirectX::XMFLOAT3(200.f, 360.f, 0.f)));
        m_ObjectManager->Register(new Button("quit_ui", "start_ui", NextScene, DirectX::XMFLOAT3(800.f, 360.f, 0.f)));

        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI TitleScene::LoadResources(LPVOID lpParam_)
{
    TextureManager::GetInstance()->Load("Res/Textures/title_bg.png", "bg");
    TextureManager::GetInstance()->Load("Res/Textures/title_ui_quit.png", "quit_ui");
    TextureManager::GetInstance()->Load("Res/Textures/title_ui_start.png", "start_ui");

    return 0;
}


void TitleScene::Main()
{
    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_A))
    {
        SceneManager::GetInstance()->ChangeScene(SceneID::Game);
    }

    m_ObjectManager->Update();
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
        m_ObjectManager->Draw();
        break;
    default:
        break;
    }

   
}