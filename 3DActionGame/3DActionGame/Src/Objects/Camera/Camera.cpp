#include "Camera.h"
#include "../../Engine/Window.h"
#include "../../Engine/DirectGraphics.h"
#include "../../Engine/InputManager.h"
#include "../../Utility/Calculation.h"

void Camera::Update()
{
    // View行列設定
    DirectX::XMVECTOR eye   = DirectX::XMVectorSet(m_Pos.x, m_Pos.y, m_Pos.z, 0.0f);
    DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_LookAt.x, m_LookAt.y, m_LookAt.z, 0.0f);
    DirectX::XMVECTOR up    = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view_matrix = DirectX::XMMatrixLookAtLH(eye, focus, up);
    
       
    DirectX::XMStoreFloat4x4(&DirectGraphics::GetInstance()->GetConstantBufferData()->View, DirectX::XMMatrixTranspose(view_matrix));
    DirectX::XMStoreFloat4(&DirectGraphics::GetInstance()->GetConstantBufferData()->CameraPos, eye);
    
}

void Camera::Draw()
{
}

DirectX::XMFLOAT3 Camera::GetFowardNormal()
{
    DirectX::XMFLOAT3 forward;
    //! 前向きベクトルを算出する
    forward = Calculation::Sub(m_LookAt, m_Pos);
    //! 単位ベクトル化
    forward = Calculation::Normalize(forward);

    return forward;
}

DirectX::XMFLOAT3 Camera::GetLeftNormal()
{
    DirectX::XMFLOAT3 left, forward;
    forward = this->GetFowardNormal();
    //! 前向きベクトルから直角なベクトルを算出する
    left = DirectX::XMFLOAT3(forward.z, forward.y, forward.x);

    return left;
}

void Camera::Init()
{    
    m_Tag = "FollowCamera";

    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    // プロジェクション行列設定
    // 視野角
    constexpr float fov = DirectX::XMConvertToRadians(45.0f);
    // アスペクト比
    float aspect = static_cast<float>(rect.right - rect.left) / static_cast<float>(rect.bottom - rect.top);
    // Near
    float near_z = 0.1f;
    // Far
    float far_z = 500000.f;
    // プロジェクション行列の作成
    m_ProjMat = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, near_z, far_z);
    DirectX::XMStoreFloat4x4(&DirectGraphics::GetInstance()->GetConstantBufferData()->Projection, DirectX::XMMatrixTranspose(m_ProjMat));
}

void Camera::Release()
{
}
