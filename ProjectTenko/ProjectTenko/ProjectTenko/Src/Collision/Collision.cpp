#include "Collision.h"
#include "Shape/AABB.h"
#include "Shape/Cylinder.h"
#include "Shape/Ray.h"
#include "Shape/Shape.h"

bool AABBAndAABB::Test(const Shape* s1_, const Shape* s2_)
{
	const AABBShape* s1 = (AABBShape*)s1_;
	const AABBShape* s2 = (AABBShape*)s2_;

	D3DXVECTOR3 s1_max = s1->GetMax(), s1_min = s1->GetMin();
	D3DXVECTOR3 s2_max = s2->GetMax(), s2_min = s2->GetMin();
	
	if (s1_min.x > s2_max.x) return false;
	if (s1_max.x < s2_min.x) return false;
	if (s1_min.y > s2_max.y) return false;
	if (s1_max.y < s2_min.y) return false;
	if (s1_min.z > s2_max.z) return false;
	if (s1_max.z < s2_min.z) return false;

	return true;
}


bool AABBAndCylinder::Test(const Shape* s1_, const Shape* s2_)
{
	const AABBShape* aabb;
	const CylinderShape* cylinder;

	D3DXVECTOR3 aabb_max, aabb_min;
	D3DXVECTOR3 circle_center_pos;
	float	    circle_radius;

	if (s1_->GetType() == SHAPE_TYPE::Shape_AABB)
	{
		aabb = (AABBShape*)s1_;
		aabb_max = aabb->GetMax();
		aabb_min = aabb->GetMin();

		cylinder = (CylinderShape*)s2_;
		circle_center_pos = cylinder->GetPos();
		circle_radius = cylinder->GetRadius();
	}
	else
	{
		aabb = (AABBShape*)s2_;
		aabb_max = aabb->GetMax();
		aabb_min = aabb->GetMin();

		cylinder = (CylinderShape*)s1_;
		circle_center_pos = cylinder->GetPos();
		circle_radius = cylinder->GetRadius();
	}

	if (circle_center_pos.x > aabb_min.x
		&& circle_center_pos.x < aabb_max.x
		&& circle_center_pos.z > aabb_max.z - circle_radius
		&& circle_center_pos.z < aabb_min.z + circle_radius) {
		return true;
	}

	if (circle_center_pos.x > aabb_min.x - circle_radius
		&& circle_center_pos.x < aabb_max.x + circle_radius
		&& circle_center_pos.z > aabb_max.z
		&& circle_center_pos.z < aabb_min.z) {
		return true;
	}

	if ((powf(aabb_min.x - circle_center_pos.x, 2)) + (powf(aabb_max.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(aabb_max.x - circle_center_pos.x, 2)) + (powf(aabb_max.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(aabb_max.x - circle_center_pos.x, 2)) + (powf(aabb_min.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(aabb_min.x - circle_center_pos.x, 2)) + (powf(aabb_min.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	return false;
}


bool AABBandRay::Test(const Shape* s1_, const Shape* s2_)
{
	const AABBShape* aabb;
	const Ray* ray;

	D3DXVECTOR3 aabb_max;
	D3DXVECTOR3 aabb_min;
	D3DXVECTOR3 ray_org;
	D3DXVECTOR3 ray_delta;

#pragma region 初期化
	if (s1_->GetType() == SHAPE_TYPE::Shape_AABB)
	{
		aabb = (AABBShape*)s1_;
		ray  = (Ray*)s2_;

		aabb_max  = aabb->GetMax();
		aabb_min  = aabb->GetMin();
		ray_org   = ray->GetOrigin();
		ray_delta = ray->GetDelta();
	}
	else {
		aabb = (AABBShape*)s2_;
		ray  = (Ray*)s1_;

		aabb_max  = aabb->GetMax();
		aabb_min  = aabb->GetMin();
		ray_org   = ray->GetOrigin();
		ray_delta = ray->GetDelta();
	}
#pragma endregion

	bool inside = true;

	float xt, xn;
	if (ray_org.x < aabb_min.x)
	{
		xt = aabb_min.x - ray_org.x;
		if (xt > ray_delta.x)return false;
		xt /= ray_delta.x;
		inside = false;
		xn = -1.0f;
	}
	else if (ray_org.x > aabb_max.x)
	{
		xt = aabb_max.x - ray_org.x;
		if (xt < ray_delta.x) return false;
		xt /= ray_delta.x;
		inside = false;
		xn = 1.0f;
	}
	else {
		xt = -1.0f;
	}

	float yt, yn;
	if (ray_org.y < aabb_min.y)
	{
		yt = aabb_min.y - ray_org.y;
		if (yt > ray_delta.y)return false;
		yt /= ray_delta.y;
		inside = false;
		yn = -1.0f;
	}
	else if (ray_org.y > aabb_max.y)
	{
		yt = aabb_max.y - ray_org.y;
		if (yt < ray_delta.y) return false;
		yt /= ray_delta.y;
		inside = false;
		yn = 1.0f;
	}
	else {
		yt = -1.0f;
	}

	float zt, zn;
	if (ray_org.z < aabb_min.z)
	{
		zt = aabb_min.z - ray_org.z;
		if (zt > ray_delta.z)return false;
		zt /= ray_delta.z;
		inside = false;
		zn = -1.0f;
	}
	else if (ray_org.z > aabb_max.z)
	{
		zt = aabb_max.z - ray_org.z;
		if (zt < ray_delta.z) return false;
		zt /= ray_delta.z;
		inside = false;
		zn = 1.0f;
	}
	else {
		zt = -1.0f;
	}

	if (inside)
	{
		return true;
	}

	int which = 0;
	float t = xt;
	if (yt > t) {
		which = 1;
		t = yt;
	}
	if (zt > t) {
		which = 2;
		t = zt;
	}

	switch (which)
	{
	case 0:	// XZ面の交差
	{
		float y = ray_org.y + ray_delta.y * t;
		if (y < aabb_min.y || y > aabb_max.y) return false;
		float z = ray_org.z + ray_delta.z * t;
		if (z < aabb_min.z || z > aabb_max.z) return false;

	}break;

	case 1:	// XY面の交差
	{
		float x = ray_org.x + ray_delta.x * t;
		if (x < aabb_min.x || x > aabb_max.x) return false;
		float z = ray_org.z + ray_delta.z * t;
		if (z < aabb_min.z || z > aabb_max.z) return false;

	}break;

	case 2:	// XY面の交差
	{
		float x = ray_org.x + ray_delta.x * t;
		if (x < aabb_min.x || x > aabb_max.x) return false;
		float y = ray_org.y + ray_delta.y * t;
		if (y < aabb_min.y || y > aabb_max.y) return false;

	}break;
	}

	return true;
}


bool CylinderAndRay::Test(const Shape* s1_, const Shape* s2_)
{
	const CylinderShape* cylinder;
	const Ray* ray;

	D3DXVECTOR3 center_pos;
	float       radius;
	float       height;

	D3DXVECTOR3 ray_start;
	D3DXVECTOR3 ray_end;


	if (s1_->GetType() == SHAPE_TYPE::Shape_Cylinder)
	{
		cylinder = (CylinderShape*)s1_;
		ray = (Ray*)s2_;
	}
	else
	{
		cylinder = (CylinderShape*)s2_;
		ray = (Ray*)s1_;
	}

	center_pos = cylinder->GetPos();
	radius     = cylinder->GetRadius();
	height     = cylinder->GetHeight();

	ray_start = ray->GetOrigin();
	ray_end   = ray_start + ray->GetDelta();

	// Rayの原点から円の中心までのベクトル
	D3DXVECTOR3 start_to_center = center_pos - ray_start;

	// Rayの終点から円の中心までのベクトル
	D3DXVECTOR3 end_to_center = center_pos - ray_end;

	// Rayの原点からRayの終点までのベクトル
	D3DXVECTOR3 start_to_end = ray_end - ray_start;

	D3DXVECTOR3 normal_start_to_end;
	D3DXVec3Normalize(&normal_start_to_end, &start_to_end);

	D3DXVECTOR3 startCenter_to_startEnd_projection;
	D3DXVec3Cross(&startCenter_to_startEnd_projection, &start_to_center, &normal_start_to_end);
	float length = D3DXVec3Length(&startCenter_to_startEnd_projection);

	if (length > radius) return false;

	float dot01 = D3DXVec3Dot(&start_to_center, &start_to_end);
	float dot02 = D3DXVec3Dot(&end_to_center, &start_to_end);

	if (dot01 * dot02 <= 0.0f) return true;

	if (D3DXVec3Length(&start_to_center) < radius ||
		D3DXVec3Length(&end_to_center) < radius)
	{
		return true;
	}

	return false;
}