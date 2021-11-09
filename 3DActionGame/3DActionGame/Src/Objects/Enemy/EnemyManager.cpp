#include "EnemyManager.h"
#include "../../GameManager/GameManager.h"

void EnemyManager::Init()
{
	// �G�l�~�[����
	m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(0.f, 0.f, 0.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(15.f, 0.f, 0.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(-15.f, 0.f, 0.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(260.f, 0.f, -119.f)));
	//m_Enemies.push_back(new Enemy(DirectX::XMFLOAT3(-325.f, 0.f, 112.f)));

	// ������
	for (Enemy* enemy : m_Enemies)
	{
		if(enemy)enemy->Init();
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		// �G�l�~�[�̐������m�F
		if (m_Enemies[i]->IsDeath() == true)
		{
			
			// ����ł�����폜
			this->Erase(i);

			// �����G�l�~�[���S�ł�����
			if (m_Enemies.empty()) {
				// �Q�[���}�l�[�W���[�ɓ`����
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
