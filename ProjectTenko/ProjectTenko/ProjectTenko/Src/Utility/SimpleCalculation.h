#ifndef SIMPLECOLLISION_H_
#define SIMPLECOLLISION_H_

#include <d3dx9.h>

class SimpleCalculation
{
public:

	static void D3DXVec3RotationX(D3DXVECTOR3* pOut_, float degree_);
	static void D3DXVec3RotationY(D3DXVECTOR3* pOut_, float degree_);
	static void D3DXVec3RotationZ(D3DXVECTOR3* pOut_, float degree_);

	template<class T>
	static void SwapData(T& data1_, T& data2_)
	{
		T tmp  = data1_;
		data1_ = data2_;
		data2_ = tmp;
	}

};

#endif