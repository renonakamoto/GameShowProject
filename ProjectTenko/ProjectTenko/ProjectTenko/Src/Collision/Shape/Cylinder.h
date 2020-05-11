#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Shape.h"
#include <d3dx9.h>

class CylinderShape : public Shape
{
public:
	CylinderShape(float radius_, float height_):
		m_Radius(radius_),
		m_Height(height_),
		m_CenterPos(D3DXVECTOR3())
	{}

	virtual ~CylinderShape() {}

	SHAPE_TYPE GetType() const       override { return SHAPE_TYPE::Shape_Cylinder; }

	void Update(const D3DXVECTOR3& pos_) override {
		m_CenterPos = pos_;
	}

	D3DXVECTOR3 GetCenterPos() const override { return m_CenterPos; }

	float GetRadius() const			 override { return m_Radius; }

	float GetHeight() const			 override { return m_Height; }

private:
	D3DXVECTOR3 m_CenterPos;	// íÜêSì_
	float       m_Radius;		// îºåa
	float       m_Height;		// çÇÇ≥

};


#endif