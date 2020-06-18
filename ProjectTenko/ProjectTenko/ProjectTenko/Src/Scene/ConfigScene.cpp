#include "ConfigScene.h"
#include "../Engine/Input/InputManager.h"
#include "../Engine/Texture/Texture.h"

ConfigScene::ConfigScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
	m_ConfigUI = new ConfigUI();

	THE_TEXTUREMANAGER->Load("assets/UI/config/config01.png");
	THE_TEXTUREMANAGER->Load("assets/UI/config/config02.png");
	THE_TEXTUREMANAGER->Load("assets/UI/config/config03.png");
	THE_TEXTUREMANAGER->Load("assets/UI/config/config04.png");

    m_ThreadHandle = CreateThread(
        nullptr,                    // �Z�L�����e�B����
        0,                          // �X�^�b�N�T�C�Y
        this->LoadResources,        // �X���b�h�֐�
        nullptr,                    // �X���b�h�֐��ɓn������
        0,                          // �쐬�I�v�V����
        &m_dwThreadID);             // �X���b�hID

    m_CurrentState = SceneState::Load;
}

ConfigScene::~ConfigScene()
{
	delete m_ConfigUI;
	m_ConfigUI = nullptr;

	THE_TEXTUREMANAGER->Release("assets/UI/config/config01.png");
	THE_TEXTUREMANAGER->Release("assets/UI/config/config02.png");
	THE_TEXTUREMANAGER->Release("assets/UI/config/config03.png");
	THE_TEXTUREMANAGER->Release("assets/UI/config/config04.png");
}

void ConfigScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI ConfigScene::LoadResources(LPVOID lpParam_)
{
    return 0;
}


void ConfigScene::Main()
{
	m_ConfigUI->Update();

	
	if (THE_INPUTMANAGER->GetMouseDown(MouseButton::Left) == false) { return; }
	if (m_ConfigUI->IsSelect(CONFIG_UI_LIST::CONFIG_UI_RETURN))
	{
		m_SceneChanger->PopScene();
	}

}

void ConfigScene::Update()
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

void ConfigScene::Draw()
{
	m_ConfigUI->Draw();

}