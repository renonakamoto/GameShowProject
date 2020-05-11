#include "Collision.h"
#include "Shape/AABB.h"
#include "Shape/Cylinder.h"

bool AABBAndAABB::Test(const Shape& s1, const Shape& s2)
{
	D3DXVECTOR3 s1_max = s1.GetMax(), s1_min = s1.GetMin();
	D3DXVECTOR3 s2_max = s2.GetMax(), s2_min = s2.GetMin();

	if (s1_min.x > s2_max.x) return false;
	if (s1_max.x < s2_min.x) return false;
	if (s1_min.y > s2_max.y) return false;
	if (s1_max.y < s2_min.y) return false;
	if (s1_min.z > s2_max.z) return false;
	if (s1_max.z < s2_min.z) return false;

	return true;
}


bool AABBandCylinder::Test(const Shape& s1, const Shape& s2)
{
	D3DXVECTOR3 s1_max = s1.GetMax(), s1_min = s1.GetMin();
	D3DXVECTOR3 circle_center_pos = s2.GetCenterPos();
	float	    circle_radius	  = s2.GetRadius();



	if (circle_center_pos.x > s1_min.x
		&& circle_center_pos.x < s1_max.x
		&& circle_center_pos.z > s1_max.z - circle_radius
		&& circle_center_pos.z < s1_min.z + circle_radius) {
		return true;
	}

	if (circle_center_pos.x > s1_min.x - circle_radius
		&& circle_center_pos.x < s1_max.x + circle_radius
		&& circle_center_pos.z > s1_max.z
		&& circle_center_pos.z < s1_min.z) {
		return true;
	}

	if ((powf(s1_min.x - circle_center_pos.x, 2)) + (powf(s1_max.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(s1_max.x - circle_center_pos.x, 2)) + (powf(s1_max.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(s1_max.x - circle_center_pos.x, 2)) + (powf(s1_min.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	if ((powf(s1_min.x - circle_center_pos.x, 2)) + (powf(s1_min.z - circle_center_pos.z, 2))
		< powf(circle_radius, 2)) {
		return true;
	}

	return false;
}

