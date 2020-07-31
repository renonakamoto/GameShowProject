#include "Merrygoland.h"

void Merrygoland::Update()
{
	CoordinateUpdate(MapData::MapObjectList::Merrygoland);
}

void Merrygoland::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}
