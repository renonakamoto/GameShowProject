#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include "../Shape/Rect.h"
#include "../Model/Model.h"


class Calculation
{
public:
	// XMFLOAT2同士の加算
	static DirectX::XMFLOAT2 Add(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);
	// XMFLOAT3同士の加算
	static DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);
	
	// XMFLOAT2同士の減算
	static DirectX::XMFLOAT2 Sub(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);
	// XMFLOAT2同士の減算
	static DirectX::XMFLOAT3 Sub(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);
	
	// XMFLOAT2同士の外積結果を返す
	static float Cross2D(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);
	// XMFLOAT3同士の外積結果を返す
	static DirectX::XMFLOAT3 Cross(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);

	// XMFLOAT2同士の内積結果を返す
	static float Dot2D(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);
	// XMFLOAT3同士の内積結果を返す
	static float Dot(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);

	static DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2 vec_);
	static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 vec_);

	// 矩形と点の当たり判定
	static bool HitRectAndPoint(Rect rect_, float x_, float y_);
	static float Length(DirectX::XMFLOAT2 vec_);
	static float Length(DirectX::XMFLOAT3 vec_);

	static float CalcPointToPlaneDistance(DirectX::XMFLOAT3 p_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_);

	static bool HitTriangleAndPoint(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_, DirectX::XMFLOAT2 c_, DirectX::XMFLOAT2 p_);

	static bool HitRayAndPlane(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_);

	static bool IntersectRayAndTriangle(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, DirectX::XMFLOAT3 c_);

private:
	Calculation(){}

	~Calculation(){}

};

#endif