
#include <math.h>
#include "Calculation.h"

DirectX::XMFLOAT2 Calculation::Add(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
{
	return DirectX::XMFLOAT2(a_.x + b_.x, a_.y + b_.y);
}

DirectX::XMFLOAT3 Calculation::Add(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
{
	return DirectX::XMFLOAT3(a_.x + b_.x, a_.y + b_.y, a_.z + b_.z);
}

DirectX::XMFLOAT2 Calculation::Sub(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
{
	return DirectX::XMFLOAT2(a_.x - b_.x, a_.y - b_.y);
}

DirectX::XMFLOAT3 Calculation::Sub(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
{
	return DirectX::XMFLOAT3(a_.x - b_.x, a_.y - b_.y, a_.z - b_.z);
}

DirectX::XMFLOAT2 Calculation::Mul(DirectX::XMFLOAT2 a_, float b_)
{
	return DirectX::XMFLOAT2(a_.x * b_, a_.y * b_);
}

DirectX::XMFLOAT3 Calculation::Mul(DirectX::XMFLOAT3 a_, float b_)
{
	return DirectX::XMFLOAT3(a_.x * b_, a_.y * b_, a_.z * b_);
}

DirectX::XMFLOAT3 Calculation::Mul(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
{
	return DirectX::XMFLOAT3(a_.x * b_.x, a_.y * b_.y, a_.z * b_.z);
}

DirectX::XMFLOAT2 Calculation::Div(DirectX::XMFLOAT2 a_, float b_)
{
	return DirectX::XMFLOAT2(a_.x / b_, a_.y / b_);
}

DirectX::XMFLOAT3 Calculation::Div(DirectX::XMFLOAT3 a_, float b_)
{
	return DirectX::XMFLOAT3(a_.x / b_, a_.y / b_, a_.z / b_);
}

float Calculation::Cross(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
{
	return (a_.x * b_.y) - (a_.y * b_.x);
}

DirectX::XMFLOAT3 Calculation::Cross(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
{
	DirectX::XMFLOAT3 result;
	
	result.x = (a_.y * b_.z) - (a_.z * b_.y);
	result.y = (a_.z * b_.x) - (a_.x * b_.z);
	result.z = (a_.x * b_.y) - (a_.y * b_.x);

	return result;
}

float Calculation::Dot(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
{
	// 各成分同士をかけて足す
	float dot = (a_.x * b_.x) + (a_.y * b_.y);
	return dot;
}

float Calculation::Dot(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
{
	// 各成分同士をかけて足す
	float dot = (a_.x * b_.x) + (a_.y * b_.y) + (a_.z * b_.z);
	return dot;
}

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

DirectX::XMFLOAT3 Calculation::InvVec(DirectX::XMFLOAT3 vec_)
{
	float inv_x = -vec_.x;
	float inv_y = -vec_.y;
	float inv_z = -vec_.z;
	return DirectX::XMFLOAT3(inv_x, inv_y, inv_z);
}

DirectX::XMFLOAT2 Calculation::InvVec(DirectX::XMFLOAT2 vec_)
{
	float inv_x = -vec_.x;
	float inv_y = -vec_.y;
	return DirectX::XMFLOAT2(inv_x, inv_y);
}

void Calculation::Clamp(float& value_, float min_, float max_)
{
	if (value_ > max_) {
		value_ = max_;
	}

	if (value_ < min_) {
		value_ = min_;
	}
}

DirectX::XMFLOAT3 Calculation::Lerp(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, float t)
{
	//0 ～ 1に収める
	Clamp(t, 0.f, 1.f);

	DirectX::XMFLOAT3 ret;
	
	// 線形補間
	ret.x = a_.x * (1.0f - t) + b_.x * t;
	ret.y = a_.y * (1.0f - t) + b_.y * t;
	ret.z = a_.z * (1.0f - t) + b_.z * t;

	return ret;
}

DirectX::XMFLOAT3 Calculation::SLerp(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, float t)
{
	DirectX::XMFLOAT3 s = a_;
	DirectX::XMFLOAT3 e = b_;

	// ベクトルの正規化
	if (s.x != 0.f || s.y != 0.0f || s.z != 0.0f)
	{
		s = Normalize(s);
	}
	if (e.x != 0.f || e.y != 0.0f || e.z != 0.0f)
	{
		e = Normalize(e);
	}
	else
	{
		return Lerp(a_, b_, t);
	}

	// 二つのベクトルの角度を算出
	float dot = Dot(s, e);

	// -1 ~ 1の間に収める
	Clamp(dot, -1.f, 1.f);

	float angle = acosf(dot);
	float sin_th = sinf(angle);
	
	float ps = sinf(angle * (1.f - t));
	float pe = sinf(angle * t);
	
	DirectX::XMFLOAT3 ret = Add(Mul(s, ps), Mul(e, pe));
	
	ret = Div(ret, sin_th);

	return Normalize(ret);
}

float Calculation::CalcPointToPlaneDistance(DirectX::XMFLOAT3 p_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_)
{
	// 面の法線
	DirectX::XMFLOAT3 plane_n = Cross(pA_, pB_);

	// 面から点へのベクトル
	DirectX::XMFLOAT3 plane_to_point = Sub(p_, pA_);

	float d = fabsf(Dot(plane_n, plane_to_point));

	float length = Length(plane_n);

	d = d / length;

	// 正規化された面の法線と面から点へのベクトルの内積の結果が距離になる
	// 裏面に点がある場合マイナスになるので、絶対値にする
	return d;	
}

bool Calculation::HitTriangleAndPoint(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_, DirectX::XMFLOAT2 c_, DirectX::XMFLOAT2 p_)
{
	// 三角形の辺の定義
	DirectX::XMFLOAT2 a_to_b = Calculation::Sub(b_, a_);
	DirectX::XMFLOAT2 b_to_c = Calculation::Sub(c_, b_);
	DirectX::XMFLOAT2 c_to_a = Calculation::Sub(a_, c_);

	// 頂点から点までのベクトルを定義
	DirectX::XMFLOAT2 a_to_p = Calculation::Sub(p_, a_);
	DirectX::XMFLOAT2 b_to_p = Calculation::Sub(p_, b_);
	DirectX::XMFLOAT2 c_to_p = Calculation::Sub(p_, c_);

	// 各辺と頂点から点までのベクトルで外積をとる
	float c1 = Calculation::Cross(a_to_b, b_to_p);
	float c2 = Calculation::Cross(b_to_c, c_to_p);
	float c3 = Calculation::Cross(c_to_a, a_to_p);

	// 外積の結果がすべて同じ符号なら三角形の中にある
	return ( (c1 >= 0 && c2 >= 0 && c3 >= 0) || (c1 <= 0 && c2 <= 0 && c3 <= 0) );
}

bool Calculation::HitRayAndPlane(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_)
{
	// 平面の法線を算出
	DirectX::XMFLOAT3 n		  = Cross(pA_, pB_);
	// レイの終点を算出
	DirectX::XMFLOAT3 ray_end = Add(rayOrigin_, rayDistance_);
	
	// 面からレイの原点へのベクトルを算出
	DirectX::XMFLOAT3 v1 = Sub(rayOrigin_, pA_);
	// 面からレイの終点へのベクトルを算出
	DirectX::XMFLOAT3 v2 = Sub(ray_end, pA_);

	// 面からレイの原点へのベクトルと面の法線との内積を算出
	float d1 = Dot(v1, n);
	// 面からレイの終点へのベクトルと面の法線との内積を算出
	float d2 = Dot(v2, n);

	// 両方が鈍角、鋭角なら交差していない
	if ((d1 * d2) > 0)
	{
		return false;
	}

	// 交差している
	return true;
}

bool Calculation::IntersectRayAndTriangle(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, DirectX::XMFLOAT3 c_, DirectX::XMFLOAT3& intersectPos_)
{
	// 三角形の辺の定義
	DirectX::XMFLOAT3 a_to_b = Calculation::Sub(b_, a_);
	DirectX::XMFLOAT3 a_to_c = Calculation::Sub(c_, a_);
	
	//// 三角形を平面として、レイが平面を貫通しているかを調べる
	//if (HitRayAndPlane(rayOrigin_, rayDistance_, a_to_b, a_to_c) == false)
	//{
	//	// 面と交差していない
	//	return false;
	//}

	// レイの終点
	DirectX::XMFLOAT3 ray_end = Calculation::Add(rayOrigin_, rayDistance_);

	// レイの原点から平面までの距離を算出
	float d1 = CalcPointToPlaneDistance(rayOrigin_, a_to_b, a_to_c);
	// レイの終点から平面までの距離を算出
	float d2 = CalcPointToPlaneDistance(ray_end, a_to_b, a_to_c);

	// レイと平面の内分比を算出
	float a = d1 / (d1 + d2);

	// 三角形のある点からレイの原点へのベクトル
	DirectX::XMFLOAT3 a_to_origin = Calculation::Sub(rayOrigin_, a_);
	// 三角形のある点からレイの終点へのベクトル
	DirectX::XMFLOAT3 a_to_end = Calculation::Sub(ray_end, a_);
	
	// 内分で貫通点を算出を算出
	DirectX::XMFLOAT3 penetration_point = Calculation::Lerp(a_to_origin, a_to_end, a);

	// 平面上で三角形に貫通点が含まれているかを調べる
	if (HitTriangleAndPoint(
		DirectX::XMFLOAT2(a_.x, a_.z),
		DirectX::XMFLOAT2(b_.x, b_.z),
		DirectX::XMFLOAT2(c_.x, c_.z),
		DirectX::XMFLOAT2(penetration_point.x, penetration_point.z)) == false)
	{
		// 交差していない
		return false;
	}

	intersectPos_ = penetration_point;

	// 交差している
	return true;
}