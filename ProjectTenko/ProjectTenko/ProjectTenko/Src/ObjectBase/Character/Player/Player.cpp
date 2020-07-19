#include "Player.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Collision/Shape/AABB.h"
#include "State/PlayerWait.h"

Player::Player(D3DXVECTOR3 pos_, std::string key_) :
	Character(pos_, key_)
{
	m_Motion		= std::make_unique<FbxMotion<PlayerMotionList>>();
	m_State			= std::make_unique<PlayerWait>();
	m_PlayerEffect  = std::make_unique<PlayerEffect>();

	m_Motion->AddMotion(PlayerMotionList::Wait,			1,	 200);
	m_Motion->AddMotion(PlayerMotionList::Walk,			211, 270);
	m_Motion->AddMotion(PlayerMotionList::Squat,		281, 340);
	m_Motion->AddMotion(PlayerMotionList::Squat_Wait,	341, 460);
	m_Motion->AddMotion(PlayerMotionList::Stand_Up,		461, 520);
	m_Motion->AddMotion(PlayerMotionList::Squat_Walk,	521, 640);
	m_Motion->AddMotion(PlayerMotionList::Squat_Scared,	651, 710);
	m_Motion->AddMotion(PlayerMotionList::Scared,		711, 725);

	m_IsSquat = false;
	m_IsMove  = false;

	m_WalkSpeed			= 5.5f;
	m_SquatWalkSpeed	= 1.0f;
	m_CenterPos			= m_Pos;
	m_Shape.push_back(new AABBShape(4.0f, 20.f, 4.0f));

}

Player::~Player()
{
	m_Motion.reset();
	m_State.reset();
	m_PlayerEffect.reset();
}

void Player::Update()
{
	if (m_RefCamera == nullptr)
	{
		m_RefCamera = THE_OBJECTMANAGER->GetCameraInstance();
	}

	Move();

	m_State->Update(this);

	if (m_IsSquat == true)
	{
		if (m_CenterPos.y >= -10.0f)m_CenterPos.y -= 10.0f / 60.0f;
	}
	else
	{
		if (m_CenterPos.y <= 0.0f)m_CenterPos.y += 10.0f / 60.0f;
	}

	// Y情報は含めたくない
	m_CenterPos.x = m_Pos.x;
	m_CenterPos.z = m_Pos.z;
	m_RefCamera->SetCamera(m_CenterPos, 30);

	// しゃがんでいたら
	if (m_IsSquat)
	{
		m_PlayerEffect->Update(PlayerEffectType::PlayerSneak);
	}
}

void Player::Draw()
{	

	D3DXMATRIX mat_rot, mat_trans;
	D3DXMatrixIdentity(&mat_rot);
	D3DXMatrixIdentity(&mat_trans);
	D3DXMatrixIdentity(&m_Mat_World);

	D3DXMatrixRotationY(&mat_rot, m_Angle);
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_rot * mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);


	if (   m_State->GetType() == PlayerMotionList::Squat
		|| m_State->GetType() == PlayerMotionList::Squat_Wait
		|| m_State->GetType() == PlayerMotionList::Squat_Walk)
	{
		m_PlayerEffect->Draw(PlayerEffectType::PlayerSneak);
	}

}

void Player::Move()
{
	D3DXVECTOR3 camera_forward  = m_RefCamera->GetForwardVec();
	D3DXVECTOR3 camera_left		= m_RefCamera->GetLeftVec();
	D3DXVECTOR3 result_move_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float	    speed			= m_WalkSpeed;


	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_W) == true)
	{
		result_move_vec.x += camera_forward.x;
		result_move_vec.z += camera_forward.z;
	}
	
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_S) == true)
	{
		result_move_vec.x -= camera_forward.x;
		result_move_vec.z -= camera_forward.z;
	}

	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_A) == true)
	{
		result_move_vec.x -= camera_left.x;
		result_move_vec.z += camera_left.z;
	}
	else if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_D) == true)
	{
		result_move_vec.x += camera_left.x;
		result_move_vec.z -= camera_left.z;
	}


	if (result_move_vec.x != 0.0f || result_move_vec.z != 0.0f)
	{
		// 現在の座標を保存する
		D3DXVECTOR3 old_pos = m_Pos;

		// ベクトルを正規化
		D3DXVec3Normalize(&result_move_vec, &result_move_vec);

		// 正規化したベクトルを加算する
		m_Pos.x += result_move_vec.x * speed;
		m_Pos.z += result_move_vec.z * speed;

		// 移動したのでコリジョンにも変更をかける
		for (const auto& shape : m_Shape)
		{
			shape->Update(m_Pos);
		}

		// 移動後障害物に当たった場合戻す
		if (THE_OBJECTMANAGER->HitPlayerAndMapObject() == true) {
			m_Pos = old_pos;
		}

		// 移動ベクトルからプレイヤーの角度を算出
		m_Angle = atan2f(result_move_vec.x, result_move_vec.z);

		    // 動いている
		    m_IsMove = true;
		    // 動いていない
	}else { m_IsMove = false; }
}

void Player::Motion(PlayerMotionList motionId_, bool isLoop_, bool* isEnd_)
{
	m_Motion->Motion(motionId_, m_FbxKey, isLoop_, isEnd_);
}

void Player::ChangeState(PlayerStateBase* state_)
{
	if (state_ == nullptr) return;

	m_State.reset(state_);
	m_State->Init(this);
}