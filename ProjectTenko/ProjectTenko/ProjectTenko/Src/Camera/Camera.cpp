#include "Camera.h"
#include "../Engine/Graphics/DirectGraphics.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Input/InputManager.h"
#include "../Collision/Shape/Ray.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/ConfigManager.h"
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

	m_Shape = new Ray();
}

Camera::Camera(D3DXVECTOR3 pos_, D3DXVECTOR3 lookAt_, D3DXVECTOR3 upVec_, float distance_)
{
	m_Pos	 = pos_;
	m_LookAt = lookAt_;
	m_UpVec  = upVec_;

	m_Yaw    = 0.0f;
	m_Pitch  = 0.0f;

	m_Distance		= distance_;

	m_Sensitivity.x = 0.0f;
	m_Sensitivity.y = 0.0f;

	m_Shape = new Ray();

	SetViewMatrix();
	SetProjectionMatrix();
}

Camera::~Camera()
{
	delete m_Shape;
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
	//float mouse_x = THE_INPUTMANAGER->GetMousePos().x;
	//float mouse_y = THE_INPUTMANAGER->GetMousePos().y;
	//int window_width  = THE_WINDOW->GetWindowWidth();
	//int window_height = THE_WINDOW->GetWindowHeight();

	//float horizon_magnification  = (float)GetSystemMetrics(SM_CXSCREEN) / (float)THE_WINDOW->GetWindowWidth();
	//float vertical_magnification = (float)GetSystemMetrics(SM_CYSCREEN) / (float)THE_WINDOW->GetWindowHeight();
	//RECT rect;
	//GetClientRect(THE_WINDOW->GetWindowHandle(), &rect);
	//rect.bottom /= horizon_magnification;
	//rect.right  /= vertical_magnification;

	////! ウィンドウの中心からカーソルの位置でベクトルを算出する
	//m_Yaw   -= (THE_INPUTMANAGER->GetMousePos().x - THE_WINDOW->GetWindowWidth()  / 2) / m_Sensitivity.x;
	//m_Pitch -= (THE_INPUTMANAGER->GetMousePos().y - THE_WINDOW->GetWindowHeight() / 2) / m_Sensitivity.y;

	////! カーソルを中心に持ってくる
	//SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
	
	RECT client_rect;
	GetClientRect(THE_WINDOW->GetWindowHandle(), &client_rect);

	// クライアントサイズの取得
	float half_gclient_width  = client_rect.right  / 2;
	float half_client_height  = client_rect.bottom / 2;

	int mouse_x = THE_INPUTMANAGER->GetMousePos().x * 0.8f;
	int mouse_y = THE_INPUTMANAGER->GetMousePos().y * 0.8f;


	// クライアントの真ん中からマウス座標へのベクトルを算出
	if (THE_CONFIGMANAGER->IsMouseFlip())
	{
		m_Yaw   += (mouse_x - half_gclient_width) / 1920.0f * 20.0f;
		m_Pitch += (mouse_y - 432.0f) / 1080.0f * 20.0f;
	}
	else
	{
		m_Yaw   -= (mouse_x - half_gclient_width) / 1920.0f * 20.0f;
		m_Pitch -= (mouse_y - 432.0f) / 1080.0f * 20.0f;
	}


	// マウスをクライアントの真ん中にもってくる
	SetCursorPos(768, 432);

	//! 縦向き回転の稼働範囲制限
	if (m_Pitch >  20.0f) { m_Pitch =  20.0f; }
	if (m_Pitch < -20.0f) { m_Pitch = -20.0f; }
	
	// 回転を反映させる
	/*m_Pos.x = m_LookAt.x + m_Distance *  sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_Pos.y = m_LookAt.y + m_Distance *  sinf(D3DXToRadian(m_Pitch));
	m_Pos.z = m_LookAt.z + m_Distance * -cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));*/

	m_Pos.x = m_LookAt.x + m_Distance *  sinf(D3DXToRadian(m_Yaw));
	m_Pos.y = 35.0f  + -m_Pitch;
	m_Pos.z = m_LookAt.z + m_Distance * -cosf(D3DXToRadian(m_Yaw));
}

void Camera::SetCamera(const D3DXVECTOR3& pos_, float distance_)
{
	D3DXVECTOR3 ray_vec = m_LookAt - m_Pos;
	if (THE_OBJECTMANAGER->HitRayAndObject(m_Pos, ray_vec) == true)
	{
		m_Distance--;
	}
	else if (m_Distance < 30)
	{
		m_Distance++;
	}
	//m_Distance = distance_;
	//! 注視点を設定
	m_LookAt = pos_;
}

void Camera::SetCameraSensitivity(float horizon_, float vertical_)
{
	m_Sensitivity.x = horizon_;
	m_Sensitivity.y = vertical_;
}

 D3DXVECTOR3 Camera::GetForwardVec()
{
	D3DXVECTOR3 forward;
	//! 前向きベクトルを算出する
	forward = m_LookAt - m_Pos;
	//! 単位ベクトル化
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

D3DXVECTOR3 Camera::GetLeftVec()
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
	m_LookAt.y += 30.0f;
	D3DXMATRIX mat_view;
	//! カメラのビュー行列の作成
	D3DXMatrixLookAtLH(&mat_view,
		&m_Pos,
		&m_LookAt,
		&m_UpVec);
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_VIEW, &mat_view);
}

void Camera::SetProjectionMatrix()
{
	D3DXMATRIX mat_proj;
	D3DXMatrixIdentity(&mat_proj);

	//! アスペクト比を算出
	D3DVIEWPORT9 vp;
	THE_GRAPHICS->GetD3DDevice()->GetViewport(&vp);
	float a = (float)vp.Width / (float)vp.Height;
	float aspect = 1.f;

	//! 視錐台の作成
	D3DXMatrixPerspectiveLH(
		&mat_proj,
		D3DXToRadian(80.0f),	//! 画角
		aspect,					//! アスペクト比
		1.1f,					//! near
		FLT_MAX);				//! far
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mat_proj);
}