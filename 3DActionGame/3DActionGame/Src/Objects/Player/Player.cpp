#include "Player.h"
#include "../../Engine/Engine.h"
#include "../../Utility/Calculation.h"
#include "PlayerState/PlayerIdleState.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../Objects/Enemy/Enemy.h"

void Player::Init()
{
	// モデル情報の取得
	m_Model = new SkeletalModel();
	m_Model->SetModel(FbxStorage::GetInstance()->GetModel("Ekard"));
	
	// プレイヤーステートの初期化
	m_State = PlayerIdleState::GetInstance();
	m_State->Enter(this);

	// 参照用オブジェクトの取得
	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
	}
	
	ObjectBase* camera = ObjectManager::GetInstance()->GetObj("FollowCamera");
	if (camera) m_Camera = dynamic_cast<FollowCamera*>(camera);
	if (m_Camera)
	{
		m_Camera->SetFollowObject(this);
		m_Camera->SetDistance(27.0f);
		m_Camera->SetOffset(DirectX::XMFLOAT3(0.0f, 9.f, 0.0f));
	}

	DirectX::XMFLOAT3 shape_pos = m_Pos;
	shape_pos.y = m_Pos.y + 4.f;
	m_Shape = new ShapeOBB(shape_pos, 1.4f, 4.f, 1.1f);
	m_OBB = dynamic_cast<ShapeOBB*>(m_Shape);

	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->Register(this);
}

void Player::Update()
{
#ifdef _DEBUG
	
	static DirectX::XMFLOAT3 offset(0.0f, 9.f, 0.0f);

	if (INPUT->GetKeyDown(KeyInfo::Key_T))
	{
		offset.y++;
		m_Camera->SetOffset(offset);
	}

	if (INPUT->GetKeyDown(KeyInfo::Key_G))
	{
		offset.y--;
		m_Camera->SetOffset(offset);
	}

#endif
	

	// プレイヤーの状態を更新する
	PlayerState* state = m_State->CheckState(this);

	// 前のフレームの状態と違った場合は更新する
	if (state != m_State)
	{
		m_State = state;
		m_State->Enter(this);
	}

	// 
	m_State->Update(this);
	
	// モーションのフレームを進める
	m_Model->Animate();
}

void Player::Draw()
{	
	GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	m_Model->Render(m_Pos, m_Scale, m_Rot);
	
	if (m_Shape)m_Shape->Draw();
	if (m_AttackVolume)m_AttackVolume->Draw();

	delete m_AttackVolume;
	m_AttackVolume = nullptr;
}

void Player::Release()
{
}

void Player::Attack()
{
	// 当たり判定の更新
	DirectX::XMFLOAT3 shape_pos = Calculation::Add(m_Pos, Calculation::Mul(m_DirectionVec, 3.f));
	shape_pos.y = m_Pos.y + 4.f;
	m_AttackVolume = new ShapeOBB(shape_pos, 3.f, 2.5f, 2.2f);
	m_AttackVolume->m_NormalDirect[0] = DirectX::XMFLOAT3(m_DirectionVec.z, m_DirectionVec.y, -m_DirectionVec.x);
	m_AttackVolume->m_NormalDirect[2] = m_DirectionVec;
	
	std::vector<Object3D*> hit_list;
	CollisionManager::GetInstance()->CheckHitObjects(*m_AttackVolume, &hit_list);
	for (auto obj : hit_list) {
		// 敵に当たっていたら
		if (obj->GetTag() == "Enemy") {
			// エネミーにダウンキャスト
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy) {
				// 敵にダメージを与える
				enemy->Damage(m_AttackPower);
			}
		}
	}
}

void Player::Move(float x_, float z_)
{
	// 移動ベクトルを正規化
	m_Velocity = DirectX::XMFLOAT3(x_, 0.f, z_);
	if (m_Velocity.x != 0.f || m_Velocity.z != 0.f)
	{
		m_Velocity = Calculation::Normalize(m_Velocity);
	}

	
	m_Velocity    = Calculation::Lerp(m_OldVelocity, m_Velocity, (m_Speed / 60.0f));
	m_OldVelocity = m_Velocity;

	if (Calculation::Length(m_Velocity) > 0.1f)
	{
		m_OldPos = m_Pos;

		float angle = atan2f(m_Velocity.x, m_Velocity.z);
		m_Rot.y = DirectX::XMConvertToDegrees(angle);

		m_Pos.x += m_Velocity.x;
		m_Pos.z += m_Velocity.z;
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);

		DirectX::XMFLOAT3 shape_pos = m_Pos;
		shape_pos.y = m_Pos.y + 4.f;
		m_OBB->m_Pos = shape_pos;
		m_OBB->m_NormalDirect[0] = Calculation::Normalize(DirectX::XMFLOAT3(m_Velocity.z, m_Velocity.y, -m_Velocity.x));
		m_OBB->m_NormalDirect[2] = Calculation::Normalize(m_Velocity);

		m_DirectionVec = Calculation::Normalize(m_Velocity);
	}
}