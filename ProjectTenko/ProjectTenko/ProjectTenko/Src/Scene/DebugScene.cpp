#include "DebugScene.h"
#include "TitleScene.h"
#include "OpeningScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "ConfigScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
#include "SceneManager.h"

#include "..//Engine/Input/InputManager.h"
#include "..//Engine/Font/Font.h"

using namespace std;

DebugScene::DebugScene(SceneChanger* sceneChanger_) : m_SceneChanger(sceneChanger_)
{

}

DebugScene::~DebugScene()
{
    while (!m_SceneList.empty())
    {
        m_SceneList.pop();
    }
}


void DebugScene::Update()
{
    if (m_SceneList.empty())
    {
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_ESC))
        {
            THE_SCENEMANAGER->GameQuit();
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_T))
        {
            m_SceneList.push(make_unique<TitleScene>(this));
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_G))
        {
            m_SceneList.push(make_unique<GameScene>(this));
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_P))
        {
            m_SceneList.push(make_unique<PauseScene>(this));
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
        {
            m_SceneList.push(make_unique<ConfigScene>(this));
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_E))
        {
            m_SceneList.push(make_unique<ClearScene>(this));
        }
        if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_O))
        {
            m_SceneList.push(make_unique<GameoverScene>(this));
        }
    }
    else
    {
        m_SceneList.top()->Update();
    }
}

void DebugScene::Draw()
{
    if (m_SceneList.empty())
    {
        string strings[7] =
        {
            "終了はESC",
            "TitleはTキー",
            "GameはGキー",
            "PauseはPキー",
            "ConfigはCキー",
            "ClearはEキー",
            "GameoverはOキー",
        };

        for (int i = 0; i < 7; i++)
        {
            THE_FONT->DrawFont
            (
                480.0f, 
                50.0f + i * 50, 
                strings[i], 
                MyFontDevice::FontSize::Regular, 
                MyFontDevice::FontColor::White
            );
        }
        
    }
    else
    {
        m_SceneList.top()->Draw();
    }
}

void DebugScene::ChangeScene(SceneID id_)
{
    while (!m_SceneList.empty())
    {
        m_SceneList.pop();
    }

    switch (id_)
    {
    case SceneID::Tilte:
        m_SceneList.push(make_unique<TitleScene>(this));
        break;
    case SceneID::Opening:
        m_SceneList.push(make_unique<OpeningScene>(this));
        break;
    case SceneID::Game:
        m_SceneList.push(make_unique<GameScene>(this));
        break;
    case SceneID::Pause:
        m_SceneList.push(make_unique<PauseScene>(this));
        break;
    case SceneID::Config:
        m_SceneList.push(make_unique<ConfigScene>(this));
        break;
    case SceneID::Clear:
        m_SceneList.push(make_unique<ClearScene>(this));
        break;
    case SceneID::Gameover:
        m_SceneList.push(make_unique<GameoverScene>(this));
        break;
    case SceneID::MaxSceneID:
        break;
    default:
        break;
    }
}

void DebugScene::PushScene(SceneID id_)
{
    switch (id_)
    {
    case SceneID::Tilte:
        m_SceneList.push(make_unique<TitleScene>(this));
        break;
    case SceneID::Opening:
        m_SceneList.push(make_unique<OpeningScene>(this));
        break;
    case SceneID::Game:
        m_SceneList.push(make_unique<GameScene>(this));
        break;
    case SceneID::Pause:
        m_SceneList.push(make_unique<PauseScene>(this));
        break;
    case SceneID::Config:
        m_SceneList.push(make_unique<ConfigScene>(this));
        break;
    case SceneID::Clear:
        m_SceneList.push(make_unique<ClearScene>(this));
        break;
    case SceneID::Gameover:
        m_SceneList.push(make_unique<GameoverScene>(this));
        break;
    case SceneID::MaxSceneID:
        break;
    default:
        break;
    }
}

void DebugScene::PopScene()
{
    if (!m_SceneList.empty())
    {
        m_SceneList.pop();
    }
}