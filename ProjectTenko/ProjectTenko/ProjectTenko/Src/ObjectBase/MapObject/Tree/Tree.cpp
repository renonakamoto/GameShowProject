#include "Tree.h"

void Tree::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Tree);
#endif

	for (const auto& itr : *m_MapObjectDataList)
	{
		int shape_num = 0;
		m_Shape[shape_num]->Update(itr.m_Pos);
		shape_num++;
	}
}

void Tree::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}
