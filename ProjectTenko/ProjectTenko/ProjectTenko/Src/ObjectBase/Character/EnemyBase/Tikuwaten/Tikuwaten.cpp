#include "Tikuwaten.h"

#include <math.h>
#include <process.h>

#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//Collision/Shape/AABB.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//..//Manager/ObjectManager.h"

Tikuwaten::Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_CrrentMotion(ChikuwaMotionList::Wait)
{
	m_Motion.AddMotion(ChikuwaMotionList::Wait,			   0,   60);
	m_Motion.AddMotion(ChikuwaMotionList::Walk,			   70,  130);
	m_Motion.AddMotion(ChikuwaMotionList::Sprint,		   140, 200);
	m_Motion.AddMotion(ChikuwaMotionList::ChangeDirection, 210, 270);

	m_Shape.push_back(new AABBShape(m_Pos ,14.0f ,40.0f, 14.0f));

	Navigator::GetInstance().GetEnemyRoute("Chikuwa", m_PatrolRoute);
	m_NextRoute = m_PatrolRoute.front();
	m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	m_Type = Objectmanager::EnemyType::Enemy_Tikuwaten;
}

void Tikuwaten::Update()
{
	m_State->Update(this);
}

void Tikuwaten::Draw()
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

void Tikuwaten::Patrol()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		return;
	}

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
	m_Motion.Motion(ChikuwaMotionList::Walk, m_FbxKey, true);
}

void Tikuwaten::Turn()
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

	m_Motion.Motion(ChikuwaMotionList::Wait, m_FbxKey, true);
}

void Tikuwaten::Chase()
{
	if (CanDetectPC() == false)
	{
		if (m_Handle == nullptr)
		{
			m_State = StateManager::GetInstance()->GetState(StateType::Thinking);
			return;
		}
		else if (WaitForSingleObject(m_Handle, 0) == WAIT_OBJECT_0)
		{
			CloseHandle(m_Handle);
			m_Handle = nullptr;
			m_State = StateManager::GetInstance()->GetState(StateType::Thinking);
			return;
		}
	}

	D3DXVECTOR3 pl_pos = m_RefPlayer->GetPos();
	pl_pos.y = 0;

	D3DXVECTOR3 vec = pl_pos - m_Pos;

	float distance = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	vec /= distance;

	D3DXVECTOR3 old_pos = m_Pos;
	m_Pos += vec * m_Speed * 3;

	for (auto e : m_Shape)
	{
		e->Update(m_Pos);
	}

	if (THE_OBJECTMANAGER->HitEnemyAndObject(Objectmanager::EnemyType::Enemy_Tikuwaten) == true)
	{
		m_Pos = old_pos;
	}
	m_Angle = atan2f(vec.x, vec.z);

	m_Motion.Motion(ChikuwaMotionList::Sprint, m_FbxKey, true);
}

void Tikuwaten::Return()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		return;
	}

	if (m_Pos == m_NextRoute)
	{
		// 次の移動ベクトルの算出
		m_NavData.Route.pop_back();

		if (m_NavData.Route.empty())
		{
			m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
			return;
		}

		m_NextRoute = m_NavData.Route.back();
		double distance = sqrtf(powf(m_NextRoute.x - m_Pos.x, 2) + powf(m_NextRoute.y - m_Pos.y, 2) + powf(m_NextRoute.z - m_Pos.z, 2));
		m_MovingVector = (m_NextRoute - m_Pos) / distance;
		m_Angle = atan2f(m_MovingVector.x, m_MovingVector.z);
	}
	else
	{
		Move();
	}
	m_Motion.Motion(ChikuwaMotionList::Walk, m_FbxKey, true);
}

void Tikuwaten::Thinking()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		return;
	}

	if (m_Handle == nullptr)
	{
		m_NavData.Route.clear();
		DecideReturnPoint();
		m_NavData.Pos = m_Pos;
		m_Handle = (HANDLE)_beginthreadex(NULL, 0, &Navigator::GetReturnRoute, static_cast<void*>(&m_NavData), 0, NULL);
	}
	else
	{
		if (WaitForSingleObject(m_Handle, 0) == WAIT_OBJECT_0)
		{
			CloseHandle(m_Handle);
			m_Handle = nullptr;
			m_State = StateManager::GetInstance()->GetState(StateType::Return);

			m_NextRoute = m_NavData.Route.back();
			double distance = sqrtf(powf(m_NextRoute.x - m_Pos.x, 2) + powf(m_NextRoute.y - m_Pos.y, 2) + powf(m_NextRoute.z - m_Pos.z, 2));
			m_MovingVector = (m_NextRoute - m_Pos) / distance;
			m_Angle = atan2f(m_MovingVector.x, m_MovingVector.z);
		}
	}

	m_Motion.Motion(ChikuwaMotionList::Wait, m_FbxKey, true);
}