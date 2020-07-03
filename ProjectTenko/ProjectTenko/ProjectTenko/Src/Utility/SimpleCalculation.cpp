#include "SimpleCalculation.h"

void SimpleCalculation::D3DXVec3RotationX(D3DXVECTOR3* pOut_, float degree_)
{
	if (!pOut_ || degree_ == 0) return;
	D3DXVECTOR3 tmp = *pOut_;

	pOut_->y = tmp.z * sinf(D3DXToRadian(degree_));
	pOut_->z = tmp.y * sinf(D3DXToRadian(degree_));
}

void SimpleCalculation::D3DXVec3RotationY(D3DXVECTOR3* pOut_, float degree_)
{
	if (!pOut_ || degree_ == 0) return;
	D3DXVECTOR3 tmp = *pOut_;

	pOut_->x = tmp.z * sinf(D3DXToRadian(degree_));
	pOut_->z = tmp.x * sinf(D3DXToRadian(degree_));
}

void SimpleCalculation::D3DXVec3RotationZ(D3DXVECTOR3* pOut_, float degree_)
{
	if (!pOut_ || degree_ == 0) return;
	D3DXVECTOR3 tmp = *pOut_;

	pOut_->x = tmp.y * sinf(D3DXToRadian(degree_));
	pOut_->y = tmp.x * sinf(D3DXToRadian(degree_));
}
