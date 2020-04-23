#include "Player.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Engine/Input/InputManager.h"

Player::Player(D3DXVECTOR3 pos_, std::string key_) :
	Character(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assts/models/player/tenko_sample02.fbx");
}

void Player::Update()
{
	Camera* ref_camera = THE_OBJECTMANAGER->GetCameraInstance();
	Move();

	ref_camera->SetCamera(m_Pos, 20);
}

void Player::Draw()
{
	D3DXMATRIX mat_rot, mat_trans;

	D3DXMatrixRotationY(&mat_rot, m_Angle);
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_rot * mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
	THE_FBXMANAGER->Animation(m_FbxKey, 1.0f / 60.0f);
}

void Player::Move()
{
	Camera* ref_camera = THE_OBJECTMANAGER->GetCameraInstance();
	float speed = m_WalkSpeed;

	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_W) == true)
	{
		m_Pos.x += ref_camera->GetForwardVec().x * speed;
		m_Pos.z += ref_camera->GetForwardVec().z * speed;

		m_Angle = atan2f(ref_camera->GetForwardVec().x, ref_camera->GetForwardVec().z);
	}
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_S) == true)
	{
		m_Pos.x -= ref_camera->GetForwardVec().x * speed;
		m_Pos.z -= ref_camera->GetForwardVec().z * speed;

		m_Angle = atan2f(-ref_camera->GetForwardVec().x, -ref_camera->GetForwardVec().z);
	}

	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_A) == true)
	{
		m_Pos.x -= ref_camera->GetLeftVec().x * speed;
		m_Pos.z += ref_camera->GetLeftVec().z * speed;

		m_Angle = atan2f(-ref_camera->GetLeftVec().x, ref_camera->GetLeftVec().z);
	}
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_A) == true)
	{
		m_Pos.x += ref_camera->GetLeftVec().x * speed;
		m_Pos.z -= ref_camera->GetLeftVec().z * speed;

		m_Angle = atan2f(ref_camera->GetLeftVec().x, -ref_camera->GetLeftVec().z);
	}
}
