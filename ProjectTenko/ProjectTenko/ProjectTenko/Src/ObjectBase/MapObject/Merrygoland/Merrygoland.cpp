#include "Merrygoland.h"

void Merrygoland::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Merrygoland);
#endif


	D3DXMATRIX mat_rot_y;
	
	// YŽ²‰ñ“]‚ðs‚¤
	D3DXMatrixRotationY(&mat_rot_y, D3DXToRadian(-m_Angle));

	// YŽ²‰ñ“]s—ñ‚ðŠù‘¶‚Ìƒ[ƒ‹ƒhs—ñ‚ÌYŽ²‰ñ“]•”•ª‚É‘ã“ü‚·‚é
	for (auto& v : m_WorldShrimpParts)
	{
		v._11 = mat_rot_y._11;
		v._13 = mat_rot_y._13;
		v._31 = mat_rot_y._31;
		v._33 = mat_rot_y._33;
	}

	m_Angle++;
	if (m_Angle > 360.0f)
	{
		m_Angle = 0;
	}
}

void Merrygoland::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Foundation)], mat_world);
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Paul)],	    mat_world);
	}

	for (const auto& mat_world : m_WorldShrimpParts)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Shrimp1)], mat_world);
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Shrimp2)], mat_world);
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Shrimp3)], mat_world);
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(MerrygolandParts::Merrygoland_Shrimp4)], mat_world);
	}
}
