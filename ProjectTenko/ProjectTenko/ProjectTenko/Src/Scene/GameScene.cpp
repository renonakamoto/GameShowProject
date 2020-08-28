#include "GameScene.h"
#include "../Manager/ObjectManager.h"
#include "../Engine/Input/InputManager.h"

GameScene::GameScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
    THE_OBJECTMANAGER->Entry(Objectmanager::ObjectType::Player);
    THE_OBJECTMANAGER->Entry(Objectmanager::ObjectType::Enemy);
    THE_OBJECTMANAGER->Entry(Objectmanager::ObjectType::Camera);

	ObjectManager::Create();

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
    THE_OBJECTMANAGER->Release(Objectmanager::ObjectType::Player);
    THE_OBJECTMANAGER->Release(Objectmanager::ObjectType::Enemy);
    THE_OBJECTMANAGER->Release(Objectmanager::ObjectType::Camera);
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
	//THE_FBXMANAGER->LoadFBXMesh("Player", "assets/models/player/tenko01.fbx");

    //THE_FBXMANAGER->LoadFBXMesh("Player", "assets/models/enemies/ebiten/Shrimp.fbx");
    //THE_FBXMANAGER->LoadFBXMesh("Player", "assets/models/enemies/ikaten/modelu.fbx");
    //THE_FBXMANAGER->LoadFBXMesh("Player", "assets/models/enemies/kabochaten/pumpkin_animation.fbx");
    //THE_FBXMANAGER->LoadFBXMesh("Player", "assets/models/enemies/sitaketen/siitake01.fbx");
    THE_FBXMANAGER->LoadFBXMesh("Tikuwaten", "assets/models/enemies/tikuwaten/chikuwa_animation.fbx");
    
    return 0;
}

void GameScene::Main()
{
	THE_OBJECTMANAGER->Update();


   if (THE_OBJECTMANAGER->HitPlayerAndClearTrigger() == true)
   {
       m_SceneChanger->ChangeScene(SceneID::Clear);
   }

    if (THE_OBJECTMANAGER->HitPlayerAndEnemy() == true)
    {
        m_SceneChanger->ChangeScene(SceneID::Gameover);
    }

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_ESC))
	{
		m_SceneChanger->PushScene(SceneID::Pause);
	}
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
    static int   load_time  = 0;
	static float load_ui_tu = 0.f;
	if (m_CurrentState == SceneState::Load) {
		THE_TEXTUREMANAGER->DrawTexture(0.f, 0.f, load_ui_tu, 0.f, "assets/UI/load.png");
		load_time++;
		if (load_time % 15 == 0)
		{
			load_ui_tu += 0.25;

			if (load_ui_tu > 1.f) { load_ui_tu = 0.f; }
		}
		return;
	}

	THE_OBJECTMANAGER->Draw();
}