#include "Ikaten.h"

#include <math.h>
#include <process.h>

#include "..//EnemyAI/StateManager.h"
#include "..//..//..//..//Collision/Shape/AABB.h"
#include "..//..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//..//Manager/ObjectManager.h"

Ikaten::Ikaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_), m_AttackRange(100.0f), m_FrameCounter(0)
{
	m_Motion.AddMotion(IkatenMotionList::Attack,	0,		259);
	m_Motion.AddMotion(IkatenMotionList::Wait,		260,	560);

	m_Shape.push_back(new AABBShape(m_Pos, 4.9, 20.3, 4.9));

	Navigator::GetInstance().GetEnemyRoute("Ika", m_PatrolRoute);
	m_NextRoute = m_PatrolRoute.front();
	m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	m_Type = Objectmanager::EnemyType::Enemy_Ikaten;
	m_Angle = D3DXToRadian(-90);
}

void Ikaten::Update()
{
	m_State->Update(this);
}

void Ikaten::Draw()
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

void Ikaten::Patrol()
{
	if (IsPlayerRanged() == true)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Attack);
		m_FrameCounter = 0;
	}

	m_Motion.Motion(IkatenMotionList::Wait, m_FbxKey, true);
}

void Ikaten::Attack()
{
	m_FrameCounter++;

	if (m_FrameCounter >= 260)
	{
		m_State = StateManager::GetInstance()->GetState(StateType::Patrol);
	}
	else if (m_FrameCounter == 210)
	{
		delete m_Shape.back();
		m_Shape.erase(m_Shape.begin() + 1);
	}
	else if (m_FrameCounter == 125)
	{
		D3DXVECTOR3 attack_pos = m_Pos;
		attack_pos.x += sinf(m_Angle) * 50;
		attack_pos.z += cosf(m_Angle) * 50;
		m_Shape.push_back(new AABBShape(attack_pos, 30.0f, 10.0f, 30.0f));
	}
	m_Motion.Motion(IkatenMotionList::Attack, m_FbxKey, false);
}

bool Ikaten::IsPlayerRanged()
{
	D3DXVECTOR3 pl_Pos = m_RefPlayer->GetPos();

	float vecX = pl_Pos.x - m_Pos.x;
	float vecZ = pl_Pos.z - m_Pos.z;

	float distance = sqrtf(vecX * vecX + vecZ * vecZ);

	if (distance > m_AttackRange)
	{
		return false;
	}

	float rotate_rad = m_Angle;

	float arc_dirX = sinf(rotate_rad);
	float arc_dirZ = cosf(rotate_rad);

	vecX /= distance;
	vecZ /= distance;

	float dot = vecX * arc_dirX + vecZ * arc_dirZ;
	float fan_cos = cosf(D3DXToRadian(ENEMY_VIEW_ANGLE / 2));

	if (fan_cos < dot)
	{
		return true;
	}

	return false;
}
