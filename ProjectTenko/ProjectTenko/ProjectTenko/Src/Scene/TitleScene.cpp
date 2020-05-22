#include "TitleScene.h"

#include "../Manager/ObjectManager.h"
#include "../Engine/Graphics/DirectGraphics.h"
#include "../Engine/Input/InputManager.h"

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

	THE_TEXTUREMANAGER->AllRelease();
}

void TitleScene::Load()
{
	THE_TEXTUREMANAGER->Load("assets/UI/title/Title_Start_UI.png");
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI TitleScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void TitleScene::Main()
{
	if (m_TitleUI != nullptr) m_TitleUI->Update();


	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_Space) == true)
	{
		m_SceneChanger->ChangeScene(SceneID::Game);
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
	if (m_TitleUI != nullptr) m_TitleUI->Draw();



}