#include "GameManager.h"
#include "../Scene/SceneManager.h"

void GameManager::GameClear()
{
	SceneManager::GetInstance()->ChangeScene(SceneID::Clear);
}

void GameManager::GameOver()
{
	SceneManager::GetInstance()->ChangeScene(SceneID::Gameover);
}
