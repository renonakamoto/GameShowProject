#ifndef SHAPE_3D_H_
#define SHAPE_3D_H_

class ShapeAABB;
class ShapeOBB;
class ShapeCapsule;

class Shape3D
{
public:
	virtual bool HitTest(Shape3D& shape_)   = 0;
	virtual bool HitTest(ShapeAABB& shape_) = 0;
	virtual bool HitTest(ShapeOBB& shape_)  = 0;
	virtual bool HitTest(ShapeCapsule& shape_)   = 0;
};

#endif