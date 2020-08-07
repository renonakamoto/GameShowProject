#include "Tikuwaten.h"

#include <math.h>
#include <process.h>

#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"

Tikuwaten::Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_CrrentMotion(ChikuwaMotionList::Wait)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/tikuwaten/chikuwa_animation.fbx");

	m_Motion.AddMotion(ChikuwaMotionList::Wait,			   0,   60);
	m_Motion.AddMotion(ChikuwaMotionList::Walk,			   70,  130);
	m_Motion.AddMotion(ChikuwaMotionList::Sprint,		   140, 200);
	m_Motion.AddMotion(ChikuwaMotionList::ChangeDirection, 210, 270);

	Navigator::GetInstance().GetEnemyRoute("Chikuwa", m_PatrolRoute);
	m_State = StateManager::GetInstance()->GetState(StateType::Move);
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
}

void Tikuwaten::Move()
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
		D3DXVECTOR3 nextpos = m_Pos + m_MovingVector * m_Speed;
		if (fabsf(nextpos.x - m_Pos.x) > fabsf(m_NextRoute.x - m_Pos.x))
		{
			m_Pos = m_NextRoute;
			m_Angle = atan2f(m_MovingVector.x, m_MovingVector.z);
		}
		else
		{
			m_Pos = nextpos;
			m_Angle = atan2f(m_MovingVector.x, m_MovingVector.z);
		}
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
		m_State = StateManager::GetInstance()->GetState(StateType::Move);
	}

	if (m_IsClockwise)
	{
		m_Angle -= ENEMY_ROTATE;
	}
	else
	{
		m_Angle += ENEMY_ROTATE;
	}
	m_Motion.Motion(ChikuwaMotionList::Wait, m_FbxKey, true);
}

void Tikuwaten::Chase()
{
	if (CanDetectPC() == false)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Return);
		return;
	}

	D3DXVECTOR3 pl_pos = m_RefPlayer->GetPos();

	D3DXVECTOR3 vec = pl_pos - m_Pos;

	float distance = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	vec /= distance;

	m_Pos += vec * m_Speed;
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
		m_ReturnRoute.pop_back();

		if (m_ReturnRoute.empty())
		{
			m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
			return;
		}

		m_NextRoute = m_ReturnRoute.back();
		double distance = sqrtf(powf(m_NextRoute.x - m_Pos.x, 2) + powf(m_NextRoute.y - m_Pos.y, 2) + powf(m_NextRoute.z - m_Pos.z, 2));
		m_MovingVector = (m_NextRoute - m_Pos) / distance;
		m_Angle = atan2f(m_MovingVector.x, m_MovingVector.z);
	}
	else
	{
		D3DXVECTOR3 nextpos = m_Pos + (m_MovingVector * m_Speed);
		if (fabs(nextpos.x - m_Pos.x) > fabs(m_NextRoute.x - m_Pos.x))
		{
			m_Pos = m_NextRoute;
		}
		else
		{
			m_Pos = nextpos;
		}
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
		DecideReturnPoint();
		NavData data = { m_ReturnRoute, m_Pos, m_NextRoute };

		m_Handle = (HANDLE)_beginthreadex(NULL, 0, &Navigator::GetReturnRoute, static_cast<void*>(&data), 0, NULL);
	}
	else
	{
		if (WaitForSingleObject(m_Handle, 0) != WAIT_OBJECT_0)
		{
			m_Handle = nullptr;
			m_State = StateManager::GetInstance()->GetState(StateType::Return);
		}
	}

	m_Motion.Motion(ChikuwaMotionList::Wait, m_FbxKey, true);
}
