#include "Player.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Collision/Shape/AABB.h"

Player::Player(D3DXVECTOR3 pos_, std::string key_) :
	Character(pos_, key_)
{
	m_Motion.AddMotion(PlayerMotionList::Wait,			1,	 200);
	m_Motion.AddMotion(PlayerMotionList::Walk,			211, 270);
	m_Motion.AddMotion(PlayerMotionList::Squat,			281, 340);
	m_Motion.AddMotion(PlayerMotionList::Squat_Wait,	341, 460);
	m_Motion.AddMotion(PlayerMotionList::Stand_Up,		461, 520);
	m_Motion.AddMotion(PlayerMotionList::Squat_Walk,	521, 640);
	m_Motion.AddMotion(PlayerMotionList::Squat_Scared,	651, 710);
	m_Motion.AddMotion(PlayerMotionList::Scared,		711, 725);

	m_CrrentMotion = PlayerMotionList::Wait;

	m_IsSquat = false;

	m_WalkSpeed = 5.5f;
	m_SquatWalkSpeed = 1.0f;
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Shape.push_back(new AABBShape(4.0f, 20.f, 4.0f));
}

void Player::Update()
{
	m_IsSquat ? m_CrrentMotion = PlayerMotionList::Squat_Wait : m_CrrentMotion = PlayerMotionList::Wait;

	Camera* ref_camera = THE_OBJECTMANAGER->GetCameraInstance();
	State();
	Move();
	ref_camera->SetCamera(m_Pos, 30);
}

void Player::Draw()
{
	Motion();

	D3DXMATRIX mat_rot, mat_trans;
	D3DXMatrixIdentity(&mat_rot);
	D3DXMatrixIdentity(&mat_trans);
	D3DXMatrixIdentity(&m_Mat_World);

	D3DXMatrixRotationY(&mat_rot, m_Angle);
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_rot * mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}

void Player::Move()
{
	Camera*     ref_camera		= THE_OBJECTMANAGER->GetCameraInstance();
	D3DXVECTOR3 camera_forward  = ref_camera->GetForwardVec();
	D3DXVECTOR3 camera_left		= ref_camera->GetLeftVec();
	D3DXVECTOR3 result_move_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float	    speed			= m_WalkSpeed;


	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_W) == true)
	{
		result_move_vec.x += camera_forward.x;
		result_move_vec.z += camera_forward.z;
	}
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_S) == true)
	{
		result_move_vec.x += -camera_forward.x;
		result_move_vec.z += -camera_forward.z;
	}

	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_A) == true)
	{
		result_move_vec.x += -camera_left.x;
		result_move_vec.z += camera_left.z;
	}
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_D) == true)
	{
		result_move_vec.x += camera_left.x;
		result_move_vec.z += -camera_left.z;
	}


	if (result_move_vec.x != 0.0f || result_move_vec.z != 0.0f)
	{
		m_OldPos = m_Pos;

		D3DXVec3Normalize(&result_move_vec, &result_move_vec);

		m_Pos.x += result_move_vec.x * speed;
		m_Pos.z += result_move_vec.z * speed;

		m_Shape[0]->Update(m_Pos);

		if (THE_OBJECTMANAGER->HitPlayerAndMapObject() == true) {
			m_Pos = m_OldPos;
		}

		m_Angle = atan2f(result_move_vec.x, result_move_vec.z);

		m_IsSquat ? m_CrrentMotion = PlayerMotionList::Squat_Walk : m_CrrentMotion = PlayerMotionList::Walk;
	}
}

void Player::Motion()
{
	if (m_CrrentMotion == PlayerMotionList::Squat)
	{
		m_Motion.Motion(m_CrrentMotion, m_FbxKey, false, nullptr);
	}
	else {
		m_Motion.Motion(m_CrrentMotion, m_FbxKey, true, nullptr);
	}
}

void Player::State()
{
	Camera* ref_camera = THE_OBJECTMANAGER->GetCameraInstance();

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C) == true)
	{
		m_IsSquat = !m_IsSquat;
		
	}

	if (m_IsSquat == true)
	{
		m_CrrentMotion = PlayerMotionList::Squat;
	}
}