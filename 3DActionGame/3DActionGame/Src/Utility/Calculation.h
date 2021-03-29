#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include "../Shape/Rect.h"


class Calculation
{
public:
	/*
		矩形と点の当たり判定
	*/
	static bool HitRectAndPoint(Rect rect_, float x_, float y_);

	static DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2 vec_);
	static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 vec_);
	static float Length(DirectX::XMFLOAT2 vec_);
	static float Length(DirectX::XMFLOAT3 vec_);
	
private:
	Calculation(){}

	~Calculation(){}

};

#endif