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

void Camera::Rotate()
{	
	RECT client_rect;
	GetClientRect(THE_WINDOW->GetWindowHandle(), &client_rect);

	// �N���C�A���g�T�C�Y�̎擾
	float half_gclient_width  = client_rect.right  / 2;
	float half_client_height  = client_rect.bottom / 2;

	int mouse_x = THE_INPUTMANAGER->GetMousePos().x * 0.8f;
	int mouse_y = THE_INPUTMANAGER->GetMousePos().y * 0.8f;


	// �N���C�A���g�̐^�񒆂���}�E�X���W�ւ̃x�N�g�����Z�o
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

	// �}�E�X���N���C�A���g�̐^�񒆂ɂ����Ă���
	SetCursorPos(768, 432);

	//! �c������]�̉ғ��͈͐���
	if (m_Pitch >  20.0f) { m_Pitch =  20.0f; }
	if (m_Pitch < -20.0f) { m_Pitch = -20.0f; }
	
	// ��]�𔽉f������
	m_Pos.x = m_LookAt.x + m_Distance *  sinf(D3DXToRadian(m_Yaw));
	m_Pos.y = 35.0f  + (-m_Pitch);
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

	//! �����_��ݒ�
	m_LookAt = pos_;
}

 D3DXVECTOR3 Camera::GetForwardVec()const
{
	D3DXVECTOR3 forward;
	//! �O�����x�N�g�����Z�o����
	forward = m_LookAt - m_Pos;
	//! �P�ʃx�N�g����
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

D3DXVECTOR3 Camera::GetLeftVec()const
{
	D3DXVECTOR3 left;
	//! �O�����x�N�g�����璼�p�ȃx�N�g�����Z�o����
	left = D3DXVECTOR3(GetForwardVec().z, GetForwardVec().y, GetForwardVec().x);
	//! �P�ʃx�N�g����
	D3DXVec3Normalize(&left, &left);

	return left;
}

void Camera::SetViewMatrix()
{
	m_LookAt.y += 30.0f;
	D3DXMATRIX mat_view;
	//! �J�����̃r���[�s��̍쐬
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

	//! �A�X�y�N�g����Z�o
	D3DVIEWPORT9 vp;
	THE_GRAPHICS->GetD3DDevice()->GetViewport(&vp);
	float a = static_cast<float>(vp.Width) / static_cast<float>(vp.Height);
	float aspect = 1.f;

	//! ������̍쐬
	D3DXMatrixPerspectiveLH(
		&mat_proj,
		D3DXToRadian(80.0f),	//! ��p
		aspect,					//! �A�X�y�N�g��
		1.1f,					//! near
		FLT_MAX);				//! far
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mat_proj);
}