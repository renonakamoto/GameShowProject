#include "SceneManager.h"
#include "DebugScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
#include "../Engine/Engine.h"

using namespace std;

SceneManager::SceneManager()
{
#ifdef _DEBUG
	m_SceneStack.push(make_shared<DebugScene>(this));
#else
	m_SceneStack.push(make_shared<TitleScene>(this));
#endif 
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
	case SceneID::Game:
		m_SceneStack.push(make_shared<GameScene>(this));
		break;
	case SceneID::Clear:
		m_SceneStack.push(make_shared<ClearScene>(this));
		break;
	case SceneID::Gameover:
		m_SceneStack.push(make_shared<GameoverScene>(this));
		break;
	case SceneID::Debug:
		m_SceneStack.push(make_shared<DebugScene>(this));
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
	case SceneID::Game:
		m_SceneStack.push(make_shared<GameScene>(this));
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
	INPUT_MANAGER->Update();
	m_SceneStack.top()->Update();
}

void SceneManager::Draw()
{
	m_SceneStack.top()->Draw();
}