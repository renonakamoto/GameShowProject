#include "ShapeAABB.h"
#include "../../../Utility/Calculation.h"

void ShapeAABB::Draw()
{
    DirectGraphics::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    DirectX::XMFLOAT3 pos   = this->CenterPos();
    DirectX::XMFLOAT3 scale = Calculation::Sub(m_Max, m_Min);
    DirectX::XMFLOAT3 rot   = DirectX::XMFLOAT3(0.f, 0.f, 0.f);

    m_AABB->Render(DirectGraphics::GetInstance(), pos, scale, rot);
}

bool ShapeAABB::HitTest(Shape3D& shape_)
{
    return shape_.HitTest(*this);
}

bool ShapeAABB::HitTest(ShapeAABB& shape_)
{
    if (m_Min.x > shape_.m_Max.x) return false;
    if (m_Max.x < shape_.m_Min.x) return false;
    if (m_Min.y > shape_.m_Max.y) return false;
    if (m_Max.y < shape_.m_Min.y) return false;
    if (m_Min.z > shape_.m_Max.z) return false;
    if (m_Max.z < shape_.m_Min.z) return false;

    return true;
}

bool ShapeAABB::HitTest(ShapeOBB& shape_)
{
    return false;
}

bool ShapeAABB::HitTest(ShapeCapsule& shape_)
{
    return false;
}

DirectX::XMFLOAT3 ShapeAABB::CenterPos()
{
    // 各軸の (Min + Max) / 2 -> 中心
    float c_x = (m_Min.x + m_Max.x) / 2.f;
    float c_y = (m_Min.y + m_Max.y) / 2.f;
    float c_z = (m_Min.z + m_Max.z) / 2.f;

    return DirectX::XMFLOAT3(c_x, c_y, c_z);
}
