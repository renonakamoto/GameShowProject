#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../ObjectManager/ShadowMapObject.h"
#include "../../Model/FbxStorage.h"
#include "../../Model/ObjFileStrage.h"
#include "../../Model/SkeletalModel.h"
#include "PlayerState/PlayerState.h"
#include "PlayerState/PlayerIdleState.h"
#include "PlayerState/PlayerRunState.h"
#include "PlayerState/PlayerAttack01State.h"
#include "PlayerState/PlayerAttack02State.h"
#include "PlayerState/PlayerHitState.h"
#include "PlayerMotion/../../Stage/Stage.h"
#include "../Camera/FollowCamera.h"
#include "../../CollisionManager/Shape/3D/OBB/ShapeOBB.h"


/**
* @brief プレイヤークラス
*/
class Player : public ShadowMapObject
{
	friend PlayerIdleState;
	friend PlayerRunState;
	friend PlayerAttack01State;
	friend PlayerAttack02State;
	friend PlayerHitState;
public:
	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	Player(DirectX::XMFLOAT3 pos_) :
#pragma region MemberInit
		ShadowMapObject(pos_, { 0.f, 0.f, 0.f }, { 0.1f, 0.1f, 0.1f }),
		m_Model(nullptr),
		m_Speed(40.f),
		m_OldPos(m_Pos),
		m_Angle(0.f),
		m_AttackPower(3),
		m_DirectionVec(0.f, 0.f, 1.f),
		m_State(nullptr),
		m_Stage(nullptr),
		m_Camera(nullptr),
		m_Velocity(0.f, 0.f, 0.f), 
		m_OldVelocity(0.f, 0.f, 0.f), 
		m_OBB(nullptr),
		m_AttackVolume(nullptr),
		m_AttackVolumLength(3.f, 2.5f, 2.2f),
		m_AttackForwardDistance(3.f),
		m_PlayerSize(2.8f, 8.f, 2.2f),
		m_RotateSpeed(10.f),
		m_Hp(10),
		m_IsHit(false),
		m_IsDeath(false),
		m_CameraDistance(27.0f),
		m_CameraHeight(9.0f),
		m_CameraLookAtOffset(0.0f, 9.f, 0.0f)
#pragma endregion
	{
		m_Tag = "Player";
	}
	
	/**
	* @brief デストラクタ
	*/
	~Player()
	{
		Release();
	}

	/**
	* @fn void Init()
	* @brief 初期化関数
	*/
	void Init() override;

	/**
	* @fn void Update()
	* @brief 更新関数
	*/
	void Update()override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	*/
	void Draw()override;

	/**
	* @fn void Draw()
	* @brief シャドウマップ描画関数
	*/
	void DrawShadowMap() override;

	/**
	* @fn void SetMotion(std::string keyword_)
	* @brief プレイヤーのモーションを設定関数
	* @param[in] keyword_ モーションに紐づけているキーワード
	* @details 現在のモーションと違うモーションをセットした場合、フレームは1になる
	*/
	void SetMotion(std::string keyword_) { m_Model->Play(keyword_); }

	/**
	* @fn DirectX::XMFLOAT3 GetVelocity()
	* @brief Velocityの取得関数
	* @return DirectX::XMFLOAT3 Velocity
	*/
	DirectX::XMFLOAT3 GetVelocity() { return m_Velocity; }

	/**
	* @fn void SetVelocity(DirectX::XMFLOAT3 velocity_)
	* @brief Velocityのセット関数
	* @param[in] velocity_ Velocity
	*/
	void SetVelocity(DirectX::XMFLOAT3 velocity_) { m_Velocity = velocity_; }

	/**
	* @fn void Damage(int damageNum_)
	* @brief プレイヤーのHPを減らす関数
	* @param[in] damageNum_ 受けるダメージ数
	* @details HPが0以下になったら死亡する
	*/
	void Damage(int damageNum_);

	/**
	* @fn int GetHp()
	* @brief HPの取得関数
	* @return int HP
	*/
	int GetHp() { return m_Hp; }

private:
	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release()override;

	/**
	* @fn void Attack()
	* @brief 攻撃する関数
	* @details 敵と当たっているかを判定して当たっていた場合敵にダメージを与える
	*/
	void Attack();

	/**
	* @fn void Move(float x_, float z_)
	* @brief 移動関数
	* @param[in] x_ x軸の移動量
	* @param[in] z_ z軸の移動量
	* @details 移動後、向きベクトルとプレイヤーの高さを保存する
	*/
	void Move(float x_, float z_);

private:
	std::unique_ptr<SkeletalModel> m_Model;			//! モデル
	PlayerState*				   m_State;			//! プレイヤーの状態管理クラス
	std::unique_ptr<ShapeOBB>	   m_AttackVolume;	//! 攻撃範囲用のOBB
	DirectX::XMFLOAT3	m_AttackVolumLength;	//! 攻撃範囲のサイズ
	float				m_AttackForwardDistance;//! 攻撃の際のボリューム生成距離
	DirectX::XMFLOAT3	m_PlayerSize;			//! プレイヤーの大きさ
	DirectX::XMFLOAT3	m_DirectionVec;			//! 向きベクトル
	DirectX::XMFLOAT3	m_Velocity;				//! 現在の移動速度
	DirectX::XMFLOAT3	m_OldVelocity;			//! 1フレーム前の移動速度
	DirectX::XMFLOAT3	m_OldPos;				//! 1フレーム前の座標
	int					m_AttackPower;			//! 攻撃力
	float				m_RotateSpeed;			//! 回転速度
	float				m_Speed;				//! 移動速度
	float				m_Angle;				//!	Y軸の角度(度数法)
	int					m_Hp;					//! ヒットポイント
	bool				m_IsHit;				//! 攻撃をくらったかどうか
	bool				m_IsDeath;				//! 死んでいるかどうか

	float				m_CameraDistance;		//! カメラとの距離
	float				m_CameraHeight;			//! カメラの高さ
	DirectX::XMFLOAT3	m_CameraLookAtOffset;	//! カメラが自身を見るときの原点からのオフセット値

	ShapeOBB*			m_OBB;					//! 当たり判定用
	Stage*				m_Stage;				//! ステージ参照用変数
	FollowCamera*		m_Camera;				//! カメラ参照用変数
};

#endif