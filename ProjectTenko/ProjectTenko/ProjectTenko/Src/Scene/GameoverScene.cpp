#include "GameoverScene.h"

#include "../Engine/Input/InputManager.h"
#include "SceneManager.h"

GameoverScene::GameoverScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
    m_GameOverUI = new GameOverUI();

    m_ThreadHandle = CreateThread(
        nullptr,                    // �Z�L�����e�B����
        0,                          // �X�^�b�N�T�C�Y
        this->LoadResources,        // �X���b�h�֐�
        nullptr,                    // �X���b�h�֐��ɓn������
        0,                          // �쐬�I�v�V����
        &m_dwThreadID);             // �X���b�hID

    m_CurrentState = SceneState::Load;
}

GameoverScene::~GameoverScene()
{
    delete m_GameOverUI;
    m_GameOverUI = nullptr;
}

void GameoverScene::Load()
{

    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI GameoverScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void GameoverScene::Main()
{
    if (m_GameOverUI != nullptr) m_GameOverUI->Update();
    
    if (THE_INPUTMANAGER->GetMouseDown(MouseButton::Left) == false) { return; }

    if (m_GameOverUI->IsSelect(GAMEOVER_UI_LIST::GAMEOVER_UI_RETURN))
    {
        m_SceneChanger->ChangeScene(SceneID::Tilte);
    }
}

void GameoverScene::Update()
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

void GameoverScene::Draw()
{
    m_GameOverUI->Draw();
}