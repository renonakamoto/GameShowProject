#include "EnemyBase.h"
#include <math.h>
#include <d3dx9.h>

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

	float arc_dirX = cosf(rotate_rad);
	float arc_dirZ = sinf(rotate_rad);

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
