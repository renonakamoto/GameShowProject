#include "FollowCamera.h"
#include "../../Engine/Engine.h"

void FollowCamera::Init()
{
    Camera::Init();
}

void FollowCamera::Update()
{
    // マウスのX軸の移動量をY軸回転に加算
    m_Yaw -= INPUT->GetMouseMovementX();

    // マウス感度を取得
    float sensi = INPUT->GetMousemSensitivity();

    if (m_FollowObject)SetLookAtPos(m_FollowObject->GetPos());

    m_Pos.x = ((m_LookAt.x + m_Offset.x) + m_Distance *  sinf(DirectX::XMConvertToRadians(m_Yaw   * sensi)));
    m_Pos.y = ((m_LookAt.y + m_Offset.y));
    m_Pos.z = ((m_LookAt.z + m_Offset.z) + m_Distance * -cosf(DirectX::XMConvertToRadians(m_Yaw   * sensi)));

    
    // View行列設定
    DirectX::XMVECTOR eye         = DirectX::XMVectorSet(m_Pos.x,    m_Pos.y    + m_Height, m_Pos.z,    0.0f);
    DirectX::XMVECTOR focus       = DirectX::XMVectorSet(m_LookAt.x, m_LookAt.y + m_Height, m_LookAt.z, 0.0f);
    DirectX::XMVECTOR up          = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view_matrix = DirectX::XMMatrixLookAtLH(eye, focus, up);
    

    DirectX::XMStoreFloat4x4(&GRAPHICS->GetConstantBufferData()->View, DirectX::XMMatrixTranspose(view_matrix));
    DirectX::XMStoreFloat4(&GRAPHICS->GetConstantBufferData()->CameraPos, eye);
}
