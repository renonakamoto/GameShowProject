
#include <math.h>
#include "Calculation.h"

bool Calculation::HitRectAndPoint(Rect rect_, float x_, float y_)
{
	return ((rect_.m_Top < y_) && (rect_.m_Bottom > y_) && (rect_.m_Left < x_) && (rect_.m_Right > x_));
}

DirectX::XMFLOAT2 Calculation::Normalize(DirectX::XMFLOAT2 vec_)
{
	// ベクトルの長さを算出
	float length = Calculation::Length(vec_);
	
	// 各成分を長さで割る
	return DirectX::XMFLOAT2(vec_.x / length, vec_.y / length);
}

DirectX::XMFLOAT3 Calculation::Normalize(DirectX::XMFLOAT3 vec_)
{
	// ベクトルの長さを算出
	float length = Calculation::Length(vec_);

	// 各成分を長さで割る
	return DirectX::XMFLOAT3(vec_.x / length, vec_.y / length, vec_.z / length);
}

float Calculation::Length(DirectX::XMFLOAT2 vec_)
{
	// Xの二乗
	float x_squared = vec_.x * vec_.x;
	// Yの二乗
	float y_squared = vec_.y * vec_.y;		

	return sqrtf(x_squared + y_squared);
}

float Calculation::Length(DirectX::XMFLOAT3 vec_)
{
	// Xの二乗
	float x_squared = vec_.x * vec_.x;
	// Yの二乗
	float y_squared = vec_.y * vec_.y;
	// Zの二乗
	float z_squared = vec_.z * vec_.z;

	return sqrtf(x_squared + y_squared + z_squared);
}
