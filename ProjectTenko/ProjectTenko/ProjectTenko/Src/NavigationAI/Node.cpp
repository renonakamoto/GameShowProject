#include "Node.h"

void Route::AddPos(std::vector<D3DXVECTOR3>& route_, float size_) const
{
	D3DXVECTOR3 vec(m_Node->m_Cell.m_Column * size_, 0.0f, m_Node->m_Cell.m_Row);
	route_.push_back(vec);

	if (m_Parent == nullptr)
	{
		return;
	}

	m_Parent->AddPos(route_, size_);
}
