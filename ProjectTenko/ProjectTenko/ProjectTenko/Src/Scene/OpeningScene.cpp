#include "OpeningScene.h"

OpeningScene::OpeningScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
    m_ThreadHandle = CreateThread(
        nullptr,                    // �Z�L�����e�B����
        0,                          // �X�^�b�N�T�C�Y
        this->LoadResources,        // �X���b�h�֐�
        nullptr,                    // �X���b�h�֐��ɓn������
        0,                          // �쐬�I�v�V����
        &m_dwThreadID);             // �X���b�hID

    m_CurrentState = SceneState::Load;
}

OpeningScene::~OpeningScene()
{

}

void OpeningScene::Load()
{
    if (WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0)
    {
        m_CurrentState = SceneState::Main;
    }
}

DWORD WINAPI OpeningScene::LoadResources(LPVOID lpParam_)
{

}


void OpeningScene::Main()
{

}

void OpeningScene::Update()
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

void OpeningScene::Draw()
{

}