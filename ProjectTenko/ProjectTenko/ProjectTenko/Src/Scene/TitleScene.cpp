#include "TitleScene.h"

#include "../Manager/ObjectManager.h"
#include "../Engine/Input/InputManager.h"
#include "SceneManager.h"
#include "../Engine/Texture/Texture.h"

TitleScene::TitleScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
	m_TitleUI = new TitleUI();

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
	delete m_TitleUI;
	m_TitleUI = nullptr;

	THE_TEXTUREMANAGER->Release("assets/UI/title/title01.png");
	THE_TEXTUREMANAGER->Release("assets/UI/title/title02.png");
	THE_TEXTUREMANAGER->Release("assets/UI/title/title03.png");
	THE_TEXTUREMANAGER->Release("assets/UI/title/title04.png");
	THE_TEXTUREMANAGER->Release("assets/UI/title/title05.png");
}

void TitleScene::Load()
{
	THE_TEXTUREMANAGER->Load("assets/UI/title/title01.png");
	THE_TEXTUREMANAGER->Load("assets/UI/title/title02.png");
	THE_TEXTUREMANAGER->Load("assets/UI/title/title03.png");
	THE_TEXTUREMANAGER->Load("assets/UI/title/title04.png");
	THE_TEXTUREMANAGER->Load("assets/UI/title/title05.png");

	THE_TEXTUREMANAGER->Load("assets/UI/load.png");


    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI TitleScene::LoadResources(LPVOID lpParam_)
{
	THE_FBXMANAGER->LoadFBXMesh("Barrel", "assets/objects/barrel/Barrel.fbx");
	THE_FBXMANAGER->LoadFBXMesh("FerrisWheel", "assets/objects/ferris_wheel/dodai.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Floor", "assets/objects/floor/floor.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Gate", "assets/objects/gate/gate2.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Merrygoland", "assets/objects/merrygoland/merrygoland_Foundation.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Mountain", "assets/objects/mountain/mountain.fbx");
	THE_FBXMANAGER->LoadFBXMesh("SaplingBig", "assets/objects/sapling/NAEGI_02.fbx");
	THE_FBXMANAGER->LoadFBXMesh("SaplingSmall", "assets/objects/sapling/NAEGI_01.fbx");
	THE_FBXMANAGER->LoadFBXMesh("ShrimpStatue", "assets/objects/shrimp_statue/statue01.fbx");
	THE_FBXMANAGER->LoadFBXMesh("SkyDome", "assets/objects/skydome/sky_dome4.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Tent", "assets/objects/tent/tent.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Tree", "assets/objects/tree/wood_01.fbx");
	THE_FBXMANAGER->LoadFBXMesh("VendingMachineBlue", "assets/objects/vending_machine/Vending_machine_blue.fbx");
	// THE_FBXMANAGER->LoadFBXMesh("VendingMachineRed", "assets/objects/vending_machine/Vending_machine_Red.fbx");
	THE_FBXMANAGER->LoadFBXMesh("Wall", "assets/objects/wall/wall.fbx");

    return 0;
}


void TitleScene::Main()
{
	if (m_TitleUI != nullptr) m_TitleUI->Update();

	if (THE_INPUTMANAGER->GetMouseDown(MouseButton::Left) == false) { return; }
	
	if (m_TitleUI->IsSelect(TITLE_UI_LIST::TITLE_UI_START))
	{
		m_SceneChanger->ChangeScene(SceneID::Game);
	}
	else if (m_TitleUI->IsSelect(TITLE_UI_LIST::TITLE_UI_SETTING))
	{
		m_SceneChanger->PushScene(SceneID::Config);
	}
	else if (m_TitleUI->IsSelect(TITLE_UI_LIST::TITLE_UI_EXIT))
	{
		THE_SCENEMANAGER->GameQuit();
	}
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
	static int   load_time = 0;
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
	if (m_TitleUI != nullptr) m_TitleUI->Draw();
}