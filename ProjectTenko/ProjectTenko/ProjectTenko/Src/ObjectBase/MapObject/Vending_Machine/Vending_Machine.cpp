#include "Vending_Machine.h"

void VendingMachine::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Vending_Machine);
#endif
}

void VendingMachine::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		for (size_t i = 0; i < m_FbxKeys.size(); ++i)
		{
			THE_FBXMANAGER->Draw(m_FbxKeys[i], mat_world);
		}
	}
}
