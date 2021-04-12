﻿#ifndef SHAPE_OBB_H_
#define SHAPE_OBB_H_

#include <DirectXMath.h>
#include "../../Shape3D.h"
#include "../../../Model/ObjFileStrage.h"

class ShapeOBB : public Shape3D
{
public:
	ShapeOBB() :
		m_OBB(nullptr)
	{
		m_OBB = ObjFileStrage::GetInstance()->GetModel("Cube");
	}

	~ShapeOBB()
	{}

public:
	bool HitTest(Shape3D& shape_)override;
	bool HitTest(ShapeAABB& shape_)override;
	bool HitTest(ShapeOBB& shape_)override;
	bool HitTest(ShapeCapsule& shape_)override;

public:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_NormalDirect[3];
	float			  m_Length[3];

private:
	float LenSegOnSeparateAxis(DirectX::XMFLOAT3& spe_, DirectX::XMFLOAT3& e1_, DirectX::XMFLOAT3& e2_, DirectX::XMFLOAT3* e3_ = nullptr);

private:
	void Draw();

private:
	ObjModel* m_OBB;
	
};

#endif