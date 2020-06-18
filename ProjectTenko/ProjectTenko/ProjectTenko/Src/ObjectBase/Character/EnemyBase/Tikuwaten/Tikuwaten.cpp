#include "Tikuwaten.h"
#include <math.h>

Tikuwaten::Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/tikuwaten/chikuwa_animation.fbx");

	m_Motion.AddMotion(ChikuwaMotionList::Wait,			   0,   60);
	m_Motion.AddMotion(ChikuwaMotionList::Walk,			   70,  130);
	m_Motion.AddMotion(ChikuwaMotionList::Sprint,		   140, 200);
	m_Motion.AddMotion(ChikuwaMotionList::ChangeDirection, 210, 270);
}

void Tikuwaten::Update()
{
	switch (m_CurrentState)
	{
	case EnemyState::Patrol:
		Patrol();
		break;
	case EnemyState::Chase:
		Chase();
		break;
	case EnemyState::Return:
		Return();
		break;
	default:
		break;
	}
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
		m_CurrentState = EnemyState::Chase;
		return;
	}

	// 目的地に到達した場合の処理
	if (m_Pos == m_PatrolRoute[m_NextRoute])
	{
		if (m_PatrolRoute.size() == m_NextRoute + 1)
		{
			m_NextRoute = 0;
		}
		else
		{
			m_NextRoute += 1;
		}

		// 次の移動ベクトルの算出
		D3DXVECTOR3 vec = m_PatrolRoute[m_NextRoute];
		double distance = sqrt(pow(vec.x - m_Pos.x, 2) + pow(vec.y - m_Pos.y, 2) + pow(vec.z - m_Pos.z, 2));
		m_MovingVector = (vec - m_Pos) / distance; // 掛ける移動量
	}
	else
	{
		D3DXVECTOR3 nextpos = m_Pos + m_MovingVector;
		if (fabs(nextpos.x - m_Pos.x) > fabs(m_PatrolRoute[m_NextRoute].x - m_Pos.x))
		{
			m_Pos = m_PatrolRoute[m_NextRoute];
		}
		else
		{
			m_Pos = nextpos;
		}
	}
}

void Tikuwaten::Chase()
{
	if (CanDetectPC() == false)
	{
		m_CurrentState = EnemyState::Return;
		return;
	}
}

void Tikuwaten::Return()
{
	if (CanDetectPC() == true)
	{
		m_CurrentState = EnemyState::Chase;
		return;
	}

	D3DXVECTOR3 vec = m_ReturnRoute.back();

	if (vec == m_Pos)
	{
		// 次の移動ベクトルの算出
		m_ReturnRoute.pop_back();
		vec = m_ReturnRoute.back();
		double distance = sqrt(pow(vec.x - m_Pos.x, 2) + pow(vec.y - m_Pos.y, 2) + pow(vec.z - m_Pos.z, 2));
		m_MovingVector = (vec - m_Pos) / distance; // 掛ける移動量
	}
	else
	{
		D3DXVECTOR3 nextpos = m_Pos + m_MovingVector;
		if (fabs(nextpos.x - m_Pos.x) > fabs(m_PatrolRoute[m_NextRoute].x - m_Pos.x))
		{
			m_Pos = m_PatrolRoute[m_NextRoute];
		}
		else
		{
			m_Pos = nextpos;
		}

	}

}