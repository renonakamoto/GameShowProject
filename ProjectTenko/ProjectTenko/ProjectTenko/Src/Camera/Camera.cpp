#include "Camera.h"
#include "../Engine/Graphics/DirectGraphics.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Input/InputManager.h"
#include <math.h>


Camera::Camera()
{
	m_Pos	 = D3DXVECTOR3(0.0f, 100.0f, -10.0f);
	m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UpVec  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_Yaw	 = 0.0f;
	m_Pitch	 = 0.0f;

	m_Distance = 0.0f;

	m_Sensitivity.x = 50.0f;
	m_Sensitivity.y = 50.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Rotate();

	SetViewMatrix();
	SetProjectionMatrix();
}

void Camera::Move()
{
}

void Camera::Rotate()
{
	//! ウィンドウの中心を保存する
	D3DXVECTOR2 center_window = THE_WINDOW->GetCenterWindowPos();

	//! カーソルを中心に持ってくる
	SetCursorPos(static_cast<int>(center_window.x), static_cast<int>(center_window.y));
	
	//! ウィンドウの中心からカーソルの位置でベクトルを算出する
	m_Yaw   -= (THE_INPUTMANAGER->GetMousePos().x - center_window.x) / m_Sensitivity.x;
	m_Pitch -= (THE_INPUTMANAGER->GetMousePos().y - center_window.y) / m_Sensitivity.y;

	//! 縦向き回転の稼働範囲制限
	if (m_Pitch >  90.0f) { m_Pitch =  180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }
	
	// 回転を反映させる
	m_Pos.x = m_LookAt.x + m_Distance *  sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_Pos.y = m_LookAt.y + m_Distance *  sinf(D3DXToRadian(m_Pitch));
	m_Pos.z = m_LookAt.z + m_Distance * -cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}

void Camera::SetCamera(const D3DXVECTOR3& pos_, float distance_)
{
	m_Distance = distance_;

	//! 注視点を設定
	m_LookAt.x = pos_.x;
	m_LookAt.z = pos_.z;
}

void Camera::SetCameraSensitivity(float horizon_, float vertical_)
{
	m_Sensitivity.x = horizon_;
	m_Sensitivity.y = vertical_;
}

const D3DXVECTOR3 Camera::GetForwardVec() const
{
	D3DXVECTOR3 forward;
	//! 前向きベクトルを算出する
	forward = m_LookAt - m_Pos;
	//! 単位ベクトル化
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

const D3DXVECTOR3 Camera::GetLeftVec() const
{
	D3DXVECTOR3 left;
	//! 前向きベクトルから直角なベクトルを算出する
	left = D3DXVECTOR3(GetForwardVec().z, GetForwardVec().y, GetForwardVec().x);
	//! 単位ベクトル化
	D3DXVec3Normalize(&left, &left);

	return left;
}

void Camera::SetViewMatrix()
{
	D3DXMATRIX mat_view;
	//! カメラのビュー行列の作成
	D3DXMatrixLookAtLH(&mat_view,
		this->GetPos(),
		this->GetLookAt(),
		this->GetUpVec());
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_VIEW, &mat_view);
}

void Camera::SetProjectionMatrix()
{
	D3DXMATRIX mat_proj;
	D3DXMatrixIdentity(&mat_proj);

	//! アスペクト比を算出
	D3DVIEWPORT9 vp;
	THE_GRAPHICS->GetD3DDevice()->GetViewport(&vp);
	float aspect = static_cast<float>(vp.Width) / static_cast<float>(vp.Height);

	//! 視錐台の作成
	D3DXMatrixPerspectiveLH(
		&mat_proj,
		D3DXToRadian(60.0f),	//! 画角
		aspect,					//! アスペクト比
		1.1f,					//! near
		100000000.0f);			//! far
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mat_proj);
}
