#include "FollowCamera.h"
#include "../../Engine/DirectGraphics.h"
#include "../../Engine/InputManager.h"

void FollowCamera::Update()
{
    // マウスのX軸の移動量をY軸回転に加算
    m_Yaw   -= InputManager::GetInstance()->GetMouseMovementX();
    m_Pitch -= InputManager::GetInstance()->GetMouseMovementY();

    // マウス感度を取得
    float sensi = InputManager::GetInstance()->GetMousemSensitivity();

    SetLookAtPos(m_FollowObject->GetPos());
    
    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_Up))
    {
        m_Height++;
    }
    
    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_Down))
    {
        m_Height--;
    }

    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_Left))
    {
        m_Distance++;
    }

    if (InputManager::GetInstance()->GetKeyDown(KeyInfo::Key_Right))
    {
        m_Distance--;
    }

    m_Pos.x = ((m_LookAt.x + m_Offset.x) + m_Distance *  sinf(DirectX::XMConvertToRadians(m_Yaw   * sensi)));
    m_Pos.y = ((m_LookAt.y + m_Offset.y));// +m_Distance * sinf(DirectX::XMConvertToRadians(m_Pitch * sensi)));
    m_Pos.z = ((m_LookAt.z + m_Offset.z) + m_Distance * -cosf(DirectX::XMConvertToRadians(m_Yaw   * sensi)));

    
    // View行列設定
    DirectX::XMVECTOR eye         = DirectX::XMVectorSet(m_Pos.x,    m_Pos.y    + m_Height, m_Pos.z,    0.0f);
    DirectX::XMVECTOR focus       = DirectX::XMVectorSet(m_LookAt.x, m_LookAt.y + m_Height, m_LookAt.z, 0.0f);
    DirectX::XMVECTOR up          = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view_matrix = DirectX::XMMatrixLookAtLH(eye, focus, up);
    

    DirectX::XMStoreFloat4x4(&DirectGraphics::GetInstance()->GetConstantBufferData()->View, DirectX::XMMatrixTranspose(view_matrix));
    DirectX::XMStoreFloat4(&DirectGraphics::GetInstance()->GetConstantBufferData()->CameraPos, eye);
}
