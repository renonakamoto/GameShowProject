#ifndef SHAPE_OBB_H_
#define SHAPE_OBB_H_

#include <DirectXMath.h>
#include "../../Shape3D.h"
#include "../../../Model/ObjFileStrage.h"

class ShapeOBB : public Shape3D
{
public:
	ShapeOBB() :
		ShapeOBB(DirectX::XMFLOAT3(0.f, 0.f, 0.f), 1.f, 1.f, 1.f)
	{
	}

	ShapeOBB(DirectX::XMFLOAT3 pos_, float lengthX_, float lengthY_, float lengthZ_) :
		m_OBB(nullptr),
		m_Pos(pos_),
		m_Length{ lengthX_ , lengthY_ , lengthZ_ }
	{
		m_NormalDirect[0] = DirectX::XMFLOAT3(1.f, 0.0f, 0.0);
		m_NormalDirect[1] = DirectX::XMFLOAT3(0.f, 1.0f, 0.0);
		m_NormalDirect[2] = DirectX::XMFLOAT3(0.f, 0.0f, 1.0);

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

public:
	void Draw()override;

private:
	ObjModel* m_OBB;
	
};

#endif