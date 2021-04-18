#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "../../Model/ObjFileStrage.h"
#include "../../Model/SkeletalModel.h"
#include "PlayerState/PlayerState.h"
#include "PlayerState/PlayerRunState.h"
#include "PlayerState/PlayerAttack01State.h"
#include "PlayerState/PlayerAttack02State.h"
#include "PlayerMotion/../../Stage/Stage.h"
#include "../Camera/FollowCamera.h"
#include "../../CollisionManager/Shape/3D/OBB/ShapeOBB.h"


/**
* @brief プレイヤークラス
*/
class Player : public Object3D
{
	friend PlayerRunState;
	friend PlayerAttack01State;
	friend PlayerAttack02State;
public:
	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	Player(DirectX::XMFLOAT3 pos_) :
#pragma region MemberInit
		Object3D(pos_),
		m_Model(nullptr),
		m_Speed(4.f),
		m_OldPos(m_Pos),
		m_Angle(0.f),
		m_AttackPower(3),
		m_DirectionVec(0.f, 0.f, 1.f),
		m_State(nullptr),
		m_Stage(nullptr),
		m_Camera(nullptr),
		m_Velocity{ 0.f,0.f,0.f },
		m_OldVelocity{ 0.f,0.f,0.f },
		m_OBB(nullptr),
		m_AttackVolume(nullptr)
#pragma endregion
	{}
	
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

	void SetMotion(std::string keyword) { m_Model->Play(keyword); }

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
	SkeletalModel* m_Model;				//! モデル
	PlayerState* m_State;				//! プレイヤーの状態管理クラス
	float m_Angle;						//!	Y軸の角度(度数法)
	DirectX::XMFLOAT3 m_DirectionVec;	//! 向きベクトル
	float m_Speed;						//! 移動速度
	DirectX::XMFLOAT3 m_Velocity;		//! 現在の移動速度
	DirectX::XMFLOAT3 m_OldVelocity;	//! 1フレーム前の移動速度
	DirectX::XMFLOAT3 m_OldPos;			//! 1フレーム前の座標
	ShapeOBB* m_AttackVolume;			//! 攻撃範囲
	int m_AttackPower;					//! 攻撃力

	ShapeOBB* m_OBB;					//! 当たり判定用
	Stage* m_Stage;						//! ステージ参照用変数
	FollowCamera* m_Camera;				//! カメラ参照用変数
};

#endif