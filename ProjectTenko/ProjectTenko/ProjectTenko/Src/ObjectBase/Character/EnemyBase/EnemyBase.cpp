#include "EnemyBase.h"
#include <math.h>
#include <d3dx9.h>

#include "..//..//..//Engine/Input/InputManager.h"
#include "..//..//..//Manager/ObjectManager.h"

void Enemybase::Move()
{
	D3DXVECTOR3 old_pos = m_Pos;
	m_Pos += m_MovingVector * m_Speed;

	for (auto e : m_Shape)
	{
		e->Update(m_Pos);
	}

	if (THE_OBJECTMANAGER->HitEnemyAndObject(m_Type) == true)
	{
		m_Pos = old_pos;
		return;
	}

	if (fabsf(m_Pos.x - old_pos.x) >= fabsf(m_NextRoute.x - old_pos.x) && fabsf(m_Pos.z - old_pos.z) >= fabsf(m_NextRoute.z - old_pos.z))
	{
		m_Pos = m_NextRoute;
	}
}

void Enemybase::DecideReturnPoint()
{
	float length = INFINITY;
	for (const auto& e : m_PatrolRoute)
	{
		float tmp = sqrtf((powf(m_Pos.x - e.x, 2.0f) + powf(m_Pos.y - e.y, 2.0f) + powf(m_Pos.z - e.z, 2.0f)));
		if (length > tmp)
		{
			length = tmp;
			m_NavData.Goal = e;
		}
	}
}

bool Enemybase::CanDetectPC()
{
	D3DXVECTOR3 pl_Pos = m_RefPlayer->GetPos();

	float vecX = pl_Pos.x - m_Pos.x;
	float vecZ = pl_Pos.z - m_Pos.z;

	float distance = sqrtf(vecX * vecX + vecZ * vecZ);

	if (distance > ENEMY_VIEW)
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

	if (fan_cos > dot)
	{
		return false;
	}

	D3DXVECTOR3 enemy_eye_pos = m_Pos;
	enemy_eye_pos.y = 20.0f;
	D3DXVECTOR3 ray = pl_Pos - enemy_eye_pos;

	if (THE_OBJECTMANAGER->HitRayAndObject(enemy_eye_pos, ray) == false)
	{
		return true;
	}

	return false;
}
