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
	//! �E�B���h�E�̒��S��ۑ�����
	D3DXVECTOR2 center_window = THE_WINDOW->GetCenterWindowPos();

	//! �J�[�\���𒆐S�Ɏ����Ă���
	SetCursorPos(static_cast<int>(center_window.x), static_cast<int>(center_window.y));
	
	//! �E�B���h�E�̒��S����J�[�\���̈ʒu�Ńx�N�g�����Z�o����
	m_Yaw   -= (THE_INPUTMANAGER->GetMousePos().x - center_window.x) / m_Sensitivity.x;
	m_Pitch -= (THE_INPUTMANAGER->GetMousePos().y - center_window.y) / m_Sensitivity.y;

	//! �c������]�̉ғ��͈͐���
	if (m_Pitch >  90.0f) { m_Pitch =  180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }
	
	// ��]�𔽉f������
	m_Pos.x = m_LookAt.x + m_Distance *  sinf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
	m_Pos.y = m_LookAt.y + m_Distance *  sinf(D3DXToRadian(m_Pitch));
	m_Pos.z = m_LookAt.z + m_Distance * -cosf(D3DXToRadian(m_Yaw)) * cosf(D3DXToRadian(m_Pitch));
}

void Camera::SetCamera(const D3DXVECTOR3& pos_, float distance_)
{
	m_Distance = distance_;

	//! �����_��ݒ�
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
	//! �O�����x�N�g�����Z�o����
	forward = m_LookAt - m_Pos;
	//! �P�ʃx�N�g����
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

const D3DXVECTOR3 Camera::GetLeftVec() const
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
	D3DXMATRIX mat_view;
	//! �J�����̃r���[�s��̍쐬
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

	//! �A�X�y�N�g����Z�o
	D3DVIEWPORT9 vp;
	THE_GRAPHICS->GetD3DDevice()->GetViewport(&vp);
	float aspect = static_cast<float>(vp.Width) / static_cast<float>(vp.Height);

	//! ������̍쐬
	D3DXMatrixPerspectiveLH(
		&mat_proj,
		D3DXToRadian(60.0f),	//! ��p
		aspect,					//! �A�X�y�N�g��
		1.1f,					//! near
		100000000.0f);			//! far
	THE_GRAPHICS->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mat_proj);
}
