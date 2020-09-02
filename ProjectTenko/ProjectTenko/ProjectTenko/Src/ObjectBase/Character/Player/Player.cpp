#include "Player.h"
#include "../../../Manager/ObjectManager.h"
#include "../../../Engine/Input/InputManager.h"
#include "../../../Collision/Shape/AABB.h"
#include "State/PlayerWait.h"

Player::Player(D3DXVECTOR3 pos_, std::string key_) :
	Character(pos_, key_)
{
	m_State	= new PlayerWait();

	m_Motion.AddMotion(PlayerMotionList::Wait,			1,	 200);
	m_Motion.AddMotion(PlayerMotionList::Walk,			211, 270);
	m_Motion.AddMotion(PlayerMotionList::Squat,			281, 340);
	m_Motion.AddMotion(PlayerMotionList::Squat_Wait,	341, 460);
	m_Motion.AddMotion(PlayerMotionList::Stand_Up,		461, 520);
	m_Motion.AddMotion(PlayerMotionList::Squat_Walk,	531, 640);
	m_Motion.AddMotion(PlayerMotionList::Squat_Scared,	651, 710);
	m_Motion.AddMotion(PlayerMotionList::Scared,		711, 725);

	m_IsSquat = false;
	m_IsMove  = false;

	m_WalkSpeed			= 0.3f;
	m_SquatWalkSpeed	= 0.15f;
	m_CenterPos			= m_Pos;
	m_Shape.push_back(new AABBShape(4.0f, 20.f, 4.0f));

	m_Speed		= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Resist	= 0.3f;
	m_Force		= 0.5f;
	m_Weight	= 1.2f;

}

Player::~Player()
{
	//delete m_State;
}

void Player::Update()
{
#pragma region  デバック用
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_Z))
	{
		if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_Up))
		{
			m_WalkSpeed *= 3.0f;
			m_SquatWalkSpeed *= 3.0f;
		}

		if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_Down))
		{
			m_WalkSpeed /= 3.0f;
			m_SquatWalkSpeed /= 3.0f;
		}
	}
#pragma endregion

	Move();

	// ステイトの更新
	m_State->Update(this);

	// しゃがんでいたら
	if (m_IsSquat == true)
	{
		if (m_CenterPos.y >= -10.0f)m_CenterPos.y -= 10.0f /20.0f;
	}
	else
	{
		if (m_CenterPos.y <= 0.0f)m_CenterPos.y += 10.0f / 20.0f;
	}

	// Y情報は含めたくない
	m_CenterPos.x = m_Pos.x;
	m_CenterPos.z = m_Pos.z;

	//	カメラを移動させる
	m_Camera.SetCamera(m_CenterPos, 30);
	m_Camera.Update();

	// ワールド行列作成
	D3DXMATRIX mat_rot, mat_trans;
	D3DXMatrixIdentity(&mat_rot);
	D3DXMatrixIdentity(&mat_trans);
	D3DXMatrixIdentity(&m_Mat_World);

	D3DXMatrixRotationY(&mat_rot, m_Angle);
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_rot * mat_trans;
}

void Player::Draw()
{	
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}

void Player::Move()
{
	D3DXVECTOR3 camera_forward  = m_Camera.GetForwardVec();
	D3DXVECTOR3 camera_left		= m_Camera.GetLeftVec();
	D3DXVECTOR3 result_move_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float	    speed			= m_IsSquat ? m_SquatWalkSpeed : m_WalkSpeed;

	// 加速力
	float accele = m_Force / m_Weight;

	// キー入力に応じた移動ベクトルを出す
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_W))
	{
		result_move_vec.x += camera_forward.x;
		result_move_vec.z += camera_forward.z;
	}
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_S))
	{
		result_move_vec.x -= camera_forward.x;
		result_move_vec.z -= camera_forward.z;
	}
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_A))
	{
		result_move_vec.x -= camera_left.x;
		result_move_vec.z += camera_left.z;
	}
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_D))
	{
		result_move_vec.x += camera_left.x;
		result_move_vec.z -= camera_left.z;
	}

	// 減速
	m_Speed.x *= 1.0f - m_Resist / m_Weight;
	m_Speed.z *= 1.0f - m_Resist / m_Weight;

	// ベクトルを正規化
	D3DXVec3Normalize(&result_move_vec, &result_move_vec);

	// 正規化したベクトルをスピードに加算する
	m_Speed.x += result_move_vec.x * speed;
	m_Speed.z += result_move_vec.z * speed;

	// 動いていない時にスピードが0に近かったら0にする
	if (result_move_vec.x == 0.0f || result_move_vec.z == 0.0f)
	{
		if (m_Speed.x <= m_Resist / m_Weight && m_Speed.x >= -(m_Resist / m_Weight))
		{
			m_Speed.x = 0.0f;
		}

		if (m_Speed.z <= m_Resist / m_Weight && m_Speed.z >= -(m_Resist / m_Weight))
		{
			m_Speed.z = 0.0f;
		}

	}

	// 動いていたら
	if (m_Speed.x != 0.0f || m_Speed.z != 0.0f)
	{
		// 現在の座標を保存する
		D3DXVECTOR3 old_pos = m_Pos;

		// 速度を加算する
		m_Pos.x += m_Speed.x;
		m_Pos.z += m_Speed.z;
	
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
		m_Angle = atan2f(m_Speed.x, m_Speed.z);
	
		    // 動いている
		    m_IsMove = true;
		    // 動いていない
	}else { m_IsMove = false; }
}

void Player::Motion(PlayerMotionList motionId_, bool isLoop_, bool* isEnd_)
{
	m_Motion.Motion(motionId_, m_FbxKey, isLoop_, isEnd_);
}

void Player::ChangeState(PlayerStateBase* state_)
{
	if (state_ == nullptr) return;

	m_State = state_;
	m_State->Init(this);
}