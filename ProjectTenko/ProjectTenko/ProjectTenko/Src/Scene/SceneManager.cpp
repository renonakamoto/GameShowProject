#include "SceneManager.h"
#include "TitleScene.h"
#include "OpeningScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "ConfigScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"

#include "../Engine/Graphics/DirectGraphics.h"

using namespace std;

SceneManager::SceneManager()
{
	m_SceneStack.push(make_shared<TitleScene>(this));
	m_IsQuit = false;
}

SceneManager::~SceneManager()
{
	while (!m_SceneStack.empty())
	{
		m_SceneStack.pop();
	}
}

void SceneManager::ChangeScene(SceneID id_)
{
	while (!m_SceneStack.empty())
	{
		m_SceneStack.pop();
	}
	
	switch (id_)
	{
	case SceneID::Tilte:
		m_SceneStack.push(make_shared<TitleScene>(this));
		break;
	case SceneID::Opening:
		m_SceneStack.push(make_shared<OpeningScene>(this));
		break;
	case SceneID::Game:
		m_SceneStack.push(make_shared<GameScene>(this));
		break;
	case SceneID::Pause:
		m_SceneStack.push(make_shared<PauseScene>(this));
		break;
	case SceneID::Config:
		m_SceneStack.push(make_shared<ConfigScene>(this));
		break;
	case SceneID::Clear:
		m_SceneStack.push(make_shared<ClearScene>(this));
		break;
	case SceneID::Gameover:
		m_SceneStack.push(make_shared<GameoverScene>(this));
		break;
	case SceneID::MaxSceneID:
		break;
	default:
		break;
	}
}

void SceneManager::PushScene(SceneID id_)
{
	switch (id_)
	{
	case SceneID::Tilte:
		m_SceneStack.push(make_shared<TitleScene>(this));
		break;
	case SceneID::Opening:
		m_SceneStack.push(make_shared<OpeningScene>(this));
		break;
	case SceneID::Game:
		m_SceneStack.push(make_shared<GameScene>(this));
		break;
	case SceneID::Pause:
		m_SceneStack.push(make_shared<PauseScene>(this));
		break;
	case SceneID::Config:
		m_SceneStack.push(make_shared<ConfigScene>(this));
		break;
	case SceneID::Clear:
		m_SceneStack.push(make_shared<ClearScene>(this));
		break;
	case SceneID::Gameover:
		m_SceneStack.push(make_shared<GameoverScene>(this));
		break;
	case SceneID::MaxSceneID:
		break;
	default:
		break;
	}
}

void SceneManager::PopScene()
{
	if (m_SceneStack.size() > 1)
	{ 
		m_SceneStack.pop();
	}
}

void SceneManager::Update()
{
	m_SceneStack.top()->Update();
}

void SceneManager::Draw()
{
	THE_GRAPHICS->StartDraw();

	m_SceneStack.top()->Draw();

	THE_GRAPHICS->EndDraw();
}