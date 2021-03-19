#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
#include "../Engine/DirectGraphics.h"
#include "../Engine/InputManager.h"

using namespace std;

SceneManager::SceneManager()
{
	m_SceneStack.push(make_shared<TitleScene>(this));
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
	InputManager::GetInstance()->Update();
	m_SceneStack.top()->Update();
}

void SceneManager::Draw()
{
	DirectGraphics::GetInstance()->StartRendering();
	DirectGraphics::GetInstance()->SetUpContext();

	m_SceneStack.top()->Draw();

	DirectGraphics::GetInstance()->FinishRendering();
}