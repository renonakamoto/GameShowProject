#ifndef SHAPE_AABB_H_
#define SHAPE_AABB_H_

#include <DirectXMath.h>
#include "../../Shape3D.h"
#include "../../../Model/ObjFileStrage.h"

class ShapeAABB : public Shape3D
{
public:
	ShapeAABB(): 
		m_AABB(nullptr)
	{
		m_AABB = ObjFileStrage::GetInstance()->GetModel("Cube");
	}

	~ShapeAABB()
	{}

	void Draw();

public:
	bool HitTest(Shape3D& shape_)override;
	bool HitTest(ShapeAABB& shape_)override;
	bool HitTest(ShapeOBB& shape_)override;
	bool HitTest(ShapeCapsule& shape_)override;

public:
	DirectX::XMFLOAT3 m_Min;
	DirectX::XMFLOAT3 m_Max;

private:
	DirectX::XMFLOAT3 CenterPos();

private:
	ObjModel* m_AABB;
	
};

#endif