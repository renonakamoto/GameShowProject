#include "Tikuwaten.h"
#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"
#include <math.h>

Tikuwaten::Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_CrrentMotion(ChikuwaMotionList::Wait)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/tikuwaten/chikuwa_animation.fbx");

	m_Motion.AddMotion(ChikuwaMotionList::Wait,			   0,   60);
	m_Motion.AddMotion(ChikuwaMotionList::Walk,			   70,  130);
	m_Motion.AddMotion(ChikuwaMotionList::Sprint,		   140, 200);
	m_Motion.AddMotion(ChikuwaMotionList::ChangeDirection, 210, 270);
}

void Tikuwaten::Update()
{
	m_State->Update(this);
}

void Tikuwaten::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
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
		float angle = ((curr_vec.x * m_MovingVector.x) + (curr_vec.z * m_MovingVector.z)) /
			((sqrtf((curr_vec.x * curr_vec.x) + (curr_vec.z * curr_vec.z))) *
				(sqrtf((m_MovingVector.x * m_MovingVector.x) + (m_MovingVector.z * m_MovingVector.z))));
		
		float cross = (curr_vec.x * m_MovingVector.z) - (m_MovingVector.x * curr_vec.z);

		if (cross > 0)
		{
			m_NextAngle = m_Angle + D3DXToDegree(acosf(angle));
		}
		else
		{
			m_NextAngle = m_Angle - D3DXToDegree(acosf(angle));
		}

		m_State = StateManager::GetInstance()->GetState(StateType::Trun);
	}
	else
	{
		D3DXVECTOR3 nextpos = m_Pos + m_MovingVector * m_Speed;
		if (fabsf(nextpos.x - m_Pos.x) > fabsf(m_PatrolRoute[m_NextRouteNum].x - m_Pos.x))
		{
			m_Pos = m_PatrolRoute[m_NextRouteNum];
		}
		else
		{
			m_Pos = nextpos;
		}
	}
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

	float diff = m_NextAngle - m_Angle;
	float next_angle = m_Angle;

	if (diff > 0 && fabsf(diff) < 180)
	{
		next_angle += 5.0f;
	}
	else
	{
		next_angle -= 5.0f;
	}

	if (fabsf(next_angle - m_Angle) > fabsf(m_NextAngle - m_Angle))
	{
		m_Angle = m_NextAngle;
	}
	else
	{
		m_Angle = next_angle;
	}

	if (m_Angle > 360)
	{
		m_Angle -= 360;
	}
	else if (m_Angle < 0)
	{
		m_Angle += 360;
	}
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
}

void Tikuwaten::Return()
{
	if (CanDetectPC() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Chase);
		return;
	}

	

	D3DXVECTOR3 vec = m_ReturnRoute.back();

	if (vec == m_Pos)
	{
		// 次の移動ベクトルの算出
		m_ReturnRoute.pop_back();
		vec = m_ReturnRoute.back();
		double distance = sqrtf(powf(vec.x - m_Pos.x, 2) + powf(vec.y - m_Pos.y, 2) + powf(vec.z - m_Pos.z, 2));
		m_MovingVector = (vec - m_Pos) / distance; // 掛ける移動量
	}
	else
	{
		D3DXVECTOR3 nextpos = m_Pos + m_MovingVector;
		//if (fabs(nextpos.x - m_Pos.x) > fabs(m_PatrolRoute[m_NextRoute].x - m_Pos.x))
		//{
		//	m_Pos = m_PatrolRoute[m_NextRoute];
		//}
		//else
		//{
		//	m_Pos = nextpos;
		//}

	}

}