#include "PauseScene.h"
#include "../Engine/Input/InputManager.h"
#include "../Engine/Texture/Texture.h"

PauseScene::PauseScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
	m_PauseUI = new PauseUI();

	THE_TEXTUREMANAGER->Load("assets/UI/pause/pause01.png");
	THE_TEXTUREMANAGER->Load("assets/UI/pause/pause02.png");
	THE_TEXTUREMANAGER->Load("assets/UI/pause/pause04.png");
	THE_TEXTUREMANAGER->Load("assets/UI/pause/pause05.png");

    m_ThreadHandle = CreateThread(
        nullptr,                    // セキュリティ属性
        0,                          // スタックサイズ
        this->LoadResources,        // スレッド関数
        nullptr,                    // スレッド関数に渡す引数
        0,                          // 作成オプション
        &m_dwThreadID);             // スレッドID

    m_CurrentState = SceneState::Load;
}

PauseScene::~PauseScene()
{
	THE_TEXTUREMANAGER->Release("assets/UI/pause/pause01.png");
	THE_TEXTUREMANAGER->Release("assets/UI/pause/pause02.png");
	THE_TEXTUREMANAGER->Release("assets/UI/pause/pause04.png");
	THE_TEXTUREMANAGER->Release("assets/UI/pause/pause05.png");

	delete m_PauseUI;
	m_PauseUI = nullptr;
}

void PauseScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI PauseScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void PauseScene::Main()
{
	m_PauseUI->Update();

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_ESC))
	{
		m_SceneChanger->PopScene();
	}

	if (THE_INPUTMANAGER->GetMouseDown(MouseButton::Left) == false) { return; }
	if (m_PauseUI->IsSelect(PAUSE_UI_LIST::PAUSE_UI_RETURN_GAME))
	{
		m_SceneChanger->PopScene();
	}
	else if (m_PauseUI->IsSelect(PAUSE_UI_LIST::PAUSE_UI_RETURN_TITLE))
	{
		m_SceneChanger->ChangeScene(SceneID::Tilte);
	}
	else if (m_PauseUI->IsSelect(PAUSE_UI_LIST::PAUSE_UI_SETTING))
	{
		m_SceneChanger->PushScene(SceneID::Config);
	}

}

void PauseScene::Update()
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

void PauseScene::Draw()
{
	m_PauseUI->Draw();
}