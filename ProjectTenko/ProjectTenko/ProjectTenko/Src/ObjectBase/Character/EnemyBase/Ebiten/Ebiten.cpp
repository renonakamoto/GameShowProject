#include "Ebiten.h"

#include <math.h>
#include <process.h>

#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//Collision/Shape/AABB.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//..//Manager/ObjectManager.h"

Ebiten::Ebiten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_)
{
	m_Motion.AddMotion(EbitenMotionList::Wait, 0, 0);

	Navigator::GetInstance().GetEnemyRoute("Ebi", m_PatrolRoute);
	m_NextRoute = m_PatrolRoute.front();
	m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	m_Type = Objectmanager::EnemyType::Enemy_Ebiten;
	m_Motion.Motion(EbitenMotionList::Wait, m_FbxKey, true);
}

void Ebiten::Update()
{
	m_State->Update(this);
}

void Ebiten::Draw()
{
	D3DXMATRIX mat_trans, mat_rot;
	D3DXMatrixIdentity(&mat_rot);
	D3DXMatrixIdentity(&mat_trans);
	D3DXMatrixIdentity(&m_Mat_World);

	D3DXMatrixRotationY(&mat_rot, m_Angle);
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_rot * mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}

void Ebiten::Patrol()
{
	// 目的地に到達した場合の処理
	if (m_Pos == m_NextRoute)
	{
		D3DXVECTOR3 curr_vec = m_MovingVector;

		// 次の移動ベクトルの算出
		m_NextRouteNum++;

		if (m_PatrolRoute.size() - 1 < m_NextRouteNum)
		{
			m_NextRouteNum = 0;
		}

		m_NextRoute = m_PatrolRoute[m_NextRouteNum];
		float distance = sqrtf(powf(m_NextRoute.x - m_Pos.x, 2) + powf(m_NextRoute.y - m_Pos.y, 2) + powf(m_NextRoute.z - m_Pos.z, 2));
		m_MovingVector = (m_NextRoute - m_Pos) / distance;

		// 向きの算出
		m_NextAngle = atan2f(m_MovingVector.x, m_MovingVector.z);

		// 外積で右回りか左回りか判定
		float cross = (curr_vec.x * m_MovingVector.z) - (m_MovingVector.x * curr_vec.z);

		if (cross > 0)
		{
			m_IsClockwise = false;
		}
		else
		{
			m_IsClockwise = true;
		}

		m_State = StateManager::GetInstance()->GetState(StateType::Turn);
	}
	else
	{
		Move();
	}
}

void Ebiten::Turn()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		return;
	}

	if (m_Angle == m_NextAngle)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	}

	float new_angle = 0.0f;

	if (m_IsClockwise)
	{
		new_angle = m_Angle - ENEMY_ROTATE;
	}
	else
	{
		new_angle = m_Angle + ENEMY_ROTATE;
	}

	if (fabsf(new_angle - m_Angle) - fabsf(m_NextAngle - m_Angle))
	{
		m_Angle = m_NextAngle;
	}
	else
	{
		m_Angle = new_angle;
	}
}
