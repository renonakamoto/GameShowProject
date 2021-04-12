#ifndef SHAPE_CAPSULE_H_
#define SHAPE_CAPSULE_H_

#include "../../Shape3D.h"
#include "../../../Model/ObjFileStrage.h"

class ShapeCapsule : public Shape3D
{
public:
	bool HitTest(Shape3D& shape_)override;
	bool HitTest(ShapeAABB& shape_)override;
	bool HitTest(ShapeOBB& shape_)override;
	bool HitTest(ShapeCapsule& shape_)override;
	
};

#endif