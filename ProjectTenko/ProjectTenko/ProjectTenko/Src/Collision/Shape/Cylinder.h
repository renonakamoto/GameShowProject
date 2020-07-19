#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Shape.h"
#include <d3dx9.h>

/**
* @brief 円柱クラス
*/
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


	D3DXVECTOR3 GetPos() const override { return m_CenterPos; }

	D3DXVECTOR3 GetCenterPos() const override { return m_CenterPos; }

	float GetRadius() const			 override { return m_Radius; }

	float GetHeight() const			 override { return m_Height; }

private:
	D3DXVECTOR3 m_CenterPos;	// 中心点
	float       m_Radius;		// 半径
	float       m_Height;		// 高さ

};

#endif