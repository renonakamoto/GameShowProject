#include <sstream>
#include "GameScene.h"
#include "SceneManager.h"
#include "../Model/FbxStorage.h"
#include "../Model/ObjFileStrage.h"
#include "../Engine/DirectGraphics.h"
#include "../Engine/Texture/Texture.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Camera/FollowCamera.h"
#include "../Engine/InputManager.h"


GameScene::GameScene(SceneChanger* sceneChanger_) : 
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

GameScene::~GameScene()
{
    ObjectManager::GetInstance()->Release();
    delete m_ObjectManager;
}

void GameScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        InputManager::GetInstance()->SetInputMode(InputMode::MODE_GAME);

        ObjectManager::GetInstance()->Register(new Stage());
        ObjectManager::GetInstance()->Register(new FollowCamera());
        
        ObjectManager::GetInstance()->Register(new Player(DirectX::XMFLOAT3(0.f, 100.f, 0.f)));


        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI GameScene::LoadResources(LPVOID lpParam_)
{
    FbxStorage::GetInstance()->LoadModel("Res/Models/human222.fbx", "Ekard");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Ekard_Run_01.fbx",          "Ekard", "Run");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Ekard_Attack_01.fbx",       "Ekard", "Attack01");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Ekard_Attack_02.fbx",       "Ekard", "Attack02");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Ekard_BattleIdle_01_h.fbx", "Ekard", "Idle");
 
    ObjFileStrage::GetInstance()->LoadModel("Res/Models/Ground.obj", "Stage");

    return 0;
}

void GameScene::Main()
{
    ObjectManager::GetInstance()->Update();

    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_ESC))
    {
        if (InputManager::GetInstance()->GetInputMode() == InputMode::MODE_GAME)
        {
            InputManager::GetInstance()->SetInputMode(InputMode::MODE_UI);
        }
        else
        {
            InputManager::GetInstance()->SetInputMode(InputMode::MODE_GAME);
        }
        
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