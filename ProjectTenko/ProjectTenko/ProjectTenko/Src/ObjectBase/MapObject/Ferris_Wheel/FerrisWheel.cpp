#include "FerrisWheel.h"

void FerrisWheel::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Ferris_Wheel);
#endif

	D3DXMATRIX mat_world;
	D3DXMATRIX mat_trans;
	D3DXMATRIX mat_rot_z;

	// ZŽ²‰ñ“]‚ðs‚¤
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(m_Angle));
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, 240.f, m_Pos.z);
	mat_world = mat_rot_z * mat_trans;
	for (auto& v : m_WorldRotatingParts)
	{
		v = mat_world;
	}

	m_Angle += 1.f / 10.f;
	if (m_Angle > 360.0f)
	{
		m_Angle = 0;
	}
}

void FerrisWheel::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(FerrisWheelParts::FerrisWheel_Foundation)], mat_world);
	}

	for (const auto& mat_world : m_WorldRotatingParts)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(FerrisWheelParts::FerrisWheel_Rotating)], mat_world);
	}
}
