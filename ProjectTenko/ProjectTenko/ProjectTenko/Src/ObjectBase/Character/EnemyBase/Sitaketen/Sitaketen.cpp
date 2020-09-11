#include "Sitaketen.h"

#include <math.h>
#include <process.h>

#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//Collision/Shape/AABB.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//..//Manager/ObjectManager.h"

Sitaketen::Sitaketen(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_CurrentMotion(SitaketenMotionList::Wait), m_FrameCounter(0)
{
	m_Motion.AddMotion(SitaketenMotionList::Wait,				1,		60);
	m_Motion.AddMotion(SitaketenMotionList::Walk,				71,		150);
	m_Motion.AddMotion(SitaketenMotionList::ThrowAwayPileus,	161,	210);
	m_Motion.AddMotion(SitaketenMotionList::Sprint,				211,	250);
	m_Motion.AddMotion(SitaketenMotionList::ChangeDirection,	261,	320);
	m_Motion.AddMotion(SitaketenMotionList::WearPileus,			321,	370);

	m_Shape.push_back(new AABBShape(m_Pos, 4.9, 20.3 ,4.9));

	Navigator::GetInstance().GetEnemyRoute("Sitake", m_PatrolRoute);
	m_NextRoute = m_PatrolRoute.front();
	m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	m_Type = Objectmanager::EnemyType::Enemy_Sitaketen;
}

void Sitaketen::Update()
{
	m_State->Update(this);
}

void Sitaketen::Draw()
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

void Sitaketen::Patrol()
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
	m_Motion.Motion(SitaketenMotionList::Walk, m_FbxKey, true);
}

void Sitaketen::Turn()
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

	m_Motion.Motion(SitaketenMotionList::Wait, m_FbxKey, true);
}

void Sitaketen::Chase()
{
	if (CanDetectPC() == false)
	{
		if (m_Handle == nullptr)
		{
			m_State = StateManager::GetInstance()->GetState(StateType::Thinking);
			m_FrameCounter = 0;
			return;
		}
		else if (WaitForSingleObject(m_Handle, 0) == WAIT_OBJECT_0)
		{
			CloseHandle(m_Handle);
			m_Handle = nullptr;
			m_State = StateManager::GetInstance()->GetState(StateType::Thinking);
			m_FrameCounter = 0;
			return;
		}
	}

	if (m_FrameCounter < 50)
	{
		m_FrameCounter++;
		m_Motion.Motion(SitaketenMotionList::ThrowAwayPileus, m_FbxKey, false);
		return;
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

	m_Motion.Motion(SitaketenMotionList::Sprint, m_FbxKey, true);
}

void Sitaketen::Return()
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
	m_Motion.Motion(SitaketenMotionList::Walk, m_FbxKey, true);
}

void Sitaketen::Thinking()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		m_FrameCounter = 0;
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
		if (m_FrameCounter < 50)
		{
			m_FrameCounter++;
			m_Motion.Motion(SitaketenMotionList::WearPileus, m_FbxKey, false);
		}
		else if (WaitForSingleObject(m_Handle, 0) == WAIT_OBJECT_0)
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
	m_Motion.Motion(SitaketenMotionList::Wait, m_FbxKey, true);
}
