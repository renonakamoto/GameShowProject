#include "Node.h"

void Route::AddPos(std::vector<D3DXVECTOR3>& route_) const
{
	D3DXVECTOR3 vec(m_Node->m_Pos.x, m_Node->m_Pos.y, m_Node->m_Pos.z);
	route_.push_back(vec);

	if (m_Parent == nullptr)
	{
		return;
	}

	m_Parent->AddPos(route_);
}