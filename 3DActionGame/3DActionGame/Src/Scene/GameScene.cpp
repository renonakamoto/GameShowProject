#include <sstream>
#include "GameScene.h"
#include "SceneManager.h"
#include "../Model/FbxStorage.h"
#include "../Model/ObjFileStrage.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyManager.h"
#include "../Objects/Stage/Stage.h"
#include "../Objects/Camera/FollowCamera.h"
#include "../CollisionManager/CollisionManager.h"
#include "../GameManager/GameManager.h"
#include "../Model/FbxStorage.h"
#include "../Engine/Engine.h"

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

    TEX_MANAGER->Load("Res/Textures/nowloading.png", "NowLoading");
}

GameScene::~GameScene()
{
    CollisionManager::GetInstance()->AllRelease();
    ObjectManager::GetInstance()->AllRelease();
    TEX_MANAGER->AllRelease();
    FbxStorage::GetInstance()->AllRelease();
    ObjFileStrage::GetInstance()->AllRelease();
}

void GameScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        // リソースの読み込みが終了したら、各オブジェクトのインスタンスを作成
        ObjectManager::GetInstance()->ResisterShadowMap(new Player(DirectX::XMFLOAT3(0.f, 0.f, 0.f)));
        ObjectManager::GetInstance()->ResisterShadowMap(new EnemyManager());

        ObjectManager::GetInstance()->Register(new Stage());
        ObjectManager::GetInstance()->Register(new FollowCamera());
        
        // 各オブジェクトの生成後、各オブジェクトのInitを行う
        ObjectManager::GetInstance()->Init();
        
        m_OffScreenSprite.Init(
            GRAPHICS->GetOffScreenTextureView(), 
            WINDOW->GetClientWidth(), 
            WINDOW->GetClientHeight(),
            GRAPHICS->GetSpriteVertexShader(),
            GRAPHICS->GetBlurPixelShader()
        );

        // 入力モードを変更
        INPUT_MANAGER->SetInputMode(InputMode::MODE_GAME);
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI GameScene::LoadResources(LPVOID lpParam_)
{
    FbxStorage::GetInstance()->LoadModel("Res/Models/unitychan.fbx", "unitychan");

    // プレイヤーモデルの読み込み
    FbxStorage::GetInstance()->LoadModel("Res/Models/Player/Ekard.fbx",                  "Ekard");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Player/Ekard_Run_01.fbx",          "Ekard", "Run");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Player/Ekard_Attack_01.fbx",       "Ekard", "Attack01");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Player/Ekard_Attack_02.fbx",       "Ekard", "Attack02");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Player/Ekard_BattleIdle_01_h.fbx", "Ekard", "Idle");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Player/Ekard_Stun_01.fbx",         "Ekard", "Stun");
    FbxStorage::GetInstance()->GetModel("Ekard")->AddMesh("Res/Models/Player/Sword_12.fbx", DirectX::XMFLOAT3(22.9f, 0.0f, 40.0f), "Bip001 R Hand");

    // エネミーモデルの読み込み
    FbxStorage::GetInstance()->LoadModel("Res/Models/Enemy/Grenadier.fbx", "Enemy");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Enemy/@GrenadierWalk.fbx",        "Enemy", "Walk"  );
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Enemy/@GrenadierIdle.fbx",        "Enemy", "Idle"  );
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Enemy/@GrenadierMeleeAttack.fbx", "Enemy", "Attack");
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Enemy/@GrenadierDeath.fbx",       "Enemy", "Death" );
    FbxStorage::GetInstance()->LoadMotion("Res/Models/Enemy/@GrenadierHit.fbx",         "Enemy", "Hit"   );
    
    // ステージモデルの読み込み
    ObjFileStrage::GetInstance()->LoadModel("Res/Models/Ground.obj",     "Stage");

    // 当たり判定用のキューブモデルの読み込み
    ObjFileStrage::GetInstance()->LoadModel("Res/Models/Shape/Cube.obj", "Cube" );
    
    TEX_MANAGER->Load("Res/Textures/normal.png", "GrenadierNormalTex");
    TEX_MANAGER->Load("Res/Textures/blur_map.png", "BlurMap");

    return 0;
}

void GameScene::Main()
{
    // オブジェクトの更新
    ObjectManager::GetInstance()->Update();
    
    
#ifdef _DEBUG
    // Escキーで入力モード切替
    if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_ESC))
    {
        if (INPUT_MANAGER->GetInputMode() == InputMode::MODE_GAME)
        {
            INPUT_MANAGER->SetInputMode(InputMode::MODE_UI);
        }
        else
        {
            INPUT_MANAGER->SetInputMode(InputMode::MODE_GAME);
        }

    }
#endif
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
        GRAPHICS->RenderingPostEffect();
        {
            TEX_MANAGER->Render("NowLoading", DirectX::XMFLOAT3(0.f, 0.f, 0.f));
        }
        GRAPHICS->FinishRendering();
        break;
        
    case SceneState::Main:
        // 1パス目
    {
        GRAPHICS->StartShadwMapRendering();

        ObjectManager::GetInstance()->DrawShadowMapObj();
    }
        // 2パス目
    {
        GRAPHICS->StartRendering();

#ifdef _DEBUG
        {
            static bool is_draw = true;
            if (INPUT_MANAGER->GetKeyDown(KeyInfo::Key_Return)) is_draw = !is_draw;
            if (is_draw) {
                CollisionManager::GetInstance()->Draw();
            }
        }
#endif

        ObjectManager::GetInstance()->Draw();

        GRAPHICS->FinishRendering();
    }
        // 3パス目
    {
        GRAPHICS->RenderingPostEffect();
        m_OffScreenSprite.Draw(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
    }

        break;
    default:
        break;
    }
 
}