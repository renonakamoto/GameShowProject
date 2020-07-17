#include "EnemyBase.h"
#include <math.h>

void Enemybase::DecideReturnPoint()
{
	float length = INFINITY;
	for (const auto& e : m_PatrolRoute)
	{
		float tmp = sqrtf((powf(m_Pos.x - e.x, 2.0f) + powf(m_Pos.y - e.y, 2.0f) + powf(m_Pos.z - e.z, 2.0f)));
		if (length > tmp)
		{
			length = tmp;
			m_NextRoute = e;
		}
	}

}
