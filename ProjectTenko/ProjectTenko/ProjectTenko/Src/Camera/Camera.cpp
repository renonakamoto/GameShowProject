#include "Camera.h"
#include "../Engine/Graphics/DirectGraphics.h"
#include "../Engine/Window/Window.h"
#include <math.h>


typedef MySingletonTemplate::SingletonTemplate<MyDirectGraphics::DirectGraphics> DirectGraphics;
#define THE_GRAPHICS DirectGraphics::GetInstance()


Camera::Camera()
{
	m_Pos	 = D3DXVECTOR3(0.0f, 100.0f, -10.0f);
	m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UpVec  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_Distance = 0.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	
}

void Camera::Move()
{
}

void Camera::Rotate()
{
	SetCursorPos(960, 540);

	m_Yaw;
	m_Pitch;
	if (m_Pitch >  90.0f) { m_Pitch =  180.0f - m_Pitch; }
	if (m_Pitch < -90.0f) { m_Pitch = -180.0f - m_Pitch; }

	m_Pos.x = m_LookAt.x + m_Distance * sinf(D3DXToRadian(m_Yaw));
	m_Pos.z = m_LookAt.z + m_Distance * -cosf(D3DXToRadian(m_Yaw));
}

void Camera::SetCamera(const D3DXVECTOR3& pos_, float distance_)
{
	m_Distance = distance_;

	//! ���W��ݒ�
	m_Pos.x = pos_.x + m_Distance * sinf(m_Yaw);
	m_Pos.z = pos_.z + m_Distance * cosf(m_Yaw);

	//! �����_��ݒ�
	m_LookAt.x = pos_.x;
	m_LookAt.z = pos_.z;
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
