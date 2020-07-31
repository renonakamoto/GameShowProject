#include "FerrisWheel.h"

void FerrisWheel::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Ferris_Wheel);
}

void FerrisWheel::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}
