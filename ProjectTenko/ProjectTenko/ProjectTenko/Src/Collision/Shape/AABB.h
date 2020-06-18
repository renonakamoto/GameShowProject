#ifndef AABB_H_
#define AABB_H_

#include "Shape.h"
#include <d3dx9.h>

class AABBShape : public Shape
{
public:
	AABBShape():
		m_Width(0.0f),
		m_Height(0.0f),
		m_Depth(0.0f),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{}

	AABBShape(float width_, float height_, float depth_) :
		m_Width (width_),
		m_Height(height_),
		m_Depth (depth_),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{}

	AABBShape(D3DXVECTOR3 pos_,float width_, float height_, float depth_) :
		m_Width(width_),
		m_Height(height_),
		m_Depth(depth_),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{
		Update(pos_);
	}

	virtual ~AABBShape() {}

	SHAPE_TYPE GetType() const override { return SHAPE_TYPE::Shape_AABB; }

	void Update(const D3DXVECTOR3& pos_) override {
		float half_width  = m_Width  / 2.f;
		float half_height = m_Height / 2.f;
		float half_depth  = m_Depth  / 2.f;

		m_Min = D3DXVECTOR3(pos_.x - half_width, pos_.y - half_height, pos_.z - half_depth);
		m_Max = D3DXVECTOR3(pos_.x + half_width, pos_.y + half_height, pos_.z + half_depth);
	}

	D3DXVECTOR3 GetMin() const override { return m_Min; }
	D3DXVECTOR3 GetMax() const override { return m_Max; }

private:
	
	D3DXVECTOR3 m_Min;
	D3DXVECTOR3 m_Max;

	float m_Width;
	float m_Height;
	float m_Depth;

};

#endif