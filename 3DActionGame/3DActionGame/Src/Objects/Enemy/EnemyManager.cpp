#include "EnemyManager.h"
#include "../../GameManager/GameManager.h"

void EnemyManager::Init()
{
	// エネミー生成
	m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(0.f, 0.f, 300.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(259.f, 0.f, 184.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(260.f, 0.f, -119.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(-325.f, 0.f, 112.f)));

	// 初期化
	for (Enemy* enemy : m_Enemies)
	{
		if(enemy)enemy->Init();
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		// エネミーの生存を確認
		if (m_Enemies[i]->IsDeath() == true)
		{
			
			// 死んでいたら削除
			this->Erase(i);

			// もしエネミーが全滅したら
			if (m_Enemies.empty()) {
				// ゲームマネージャーに伝える
				GameManager::GetInstance()->GameClear();
			}
			continue;
		}

		if (m_Enemies[i])m_Enemies[i]->Update();
	}
}

void EnemyManager::Draw()
{
	for (Enemy* enemy : m_Enemies)
	{
		if (enemy)enemy->Draw();
	}
}

void EnemyManager::DrawShadowMap()
{
	for (Enemy* enemy : m_Enemies)
	{
		if (enemy)enemy->DrawShadowMap();
	}
}

void EnemyManager::Erase(int idx_)
{
	delete m_Enemies[idx_];
	m_Enemies[idx_] = nullptr;
	
	m_Enemies.erase(std::begin(m_Enemies) + idx_);
	m_Enemies.shrink_to_fit();
}

void EnemyManager::Release()
{
	if (m_Enemies.empty()) return;
	
	for (Enemy* enemy : m_Enemies)
	{
		delete enemy;
		enemy = nullptr;
	}
	m_Enemies.clear();
	m_Enemies.shrink_to_fit();
}
