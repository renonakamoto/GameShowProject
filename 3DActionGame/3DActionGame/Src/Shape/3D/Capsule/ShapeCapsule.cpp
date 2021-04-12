#include "ShapeCapsule.h"

bool ShapeCapsule::HitTest(Shape3D& shape_)
{
    return shape_.HitTest(*this);
}

bool ShapeCapsule::HitTest(ShapeAABB& shape_)
{
    return false;
}

bool ShapeCapsule::HitTest(ShapeOBB& shape_)
{
    return false;
}

bool ShapeCapsule::HitTest(ShapeCapsule& shape_)
{
    return false;
}
