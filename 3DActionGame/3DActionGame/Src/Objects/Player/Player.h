#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "../../Model/ObjFileStrage.h"
#include "PlayerMotion/PlayerState.h"
#include "PlayerMotion/RunState.h"
#include "PlayerMotion/Attack01State.h"
#include "PlayerMotion/Attack02State.h"
#include "PlayerMotion/../../Stage/Stage.h"
#include "../Camera/FollowCamera.h"
#include "../../Shape/3D/AABB/ShapeAABB.h"
#include "../../Shape/3D/OBB/ShapeOBB.h"

class Player : public Object3D
{
	friend RunState;
	friend Attack01State;
	friend Attack02State;
public:
	Player(DirectX::XMFLOAT3 pos_) :
#pragma region Member Init
		Object3D(pos_),
		m_Model(nullptr),
		m_Speed(2.f),
		m_OldPos(m_Pos),
		m_Angle(0.f),
		m_DirectionVec(0.0f, 0.0f, 1.0f),
		m_State(nullptr),
		m_Stage(nullptr),
		m_Camera(nullptr),
		m_Velocity{ 0.f,0.f,0.f },
		m_OldVelocity{ 0.f,0.f,0.f },
		m_OBB(nullptr)
#pragma endregion
	{
		Init();
	}
	
	~Player()
	{
		Release();
	}

	
	void Update()override;
	void Draw()override;

	void SetMotion(std::string keyword) { m_Model->Play(keyword); }

private:
	void Init() override;
	void Release()override;

	void Attack();
	void Move(float x_, float z_);

private:
	FbxModel*	 m_Model;				//! 
	PlayerState* m_State;				//! プレイヤーの	
	float m_Angle;						//!	Y軸の角度(度数法)
	DirectX::XMFLOAT3 m_DirectionVec;	//! 向いている方向ベクトル
	float m_Speed;						//! 移動速度
	DirectX::XMFLOAT3 m_Velocity;		//! 移動速度
	DirectX::XMFLOAT3 m_OldPos;			//! 1フレーム前の座標
	DirectX::XMFLOAT3 m_OldVelocity;	//! 1フレーム前の移動速度

	ShapeOBB* m_OBB;
	Stage* m_Stage;						//! ステージ参照用変数
	FollowCamera* m_Camera;				//! カメラ参照用変数
};

#endif