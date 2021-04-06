#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "PlayerMotion/PlayerState.h"
#include "PlayerMotion/RunState.h"
#include "PlayerMotion/Attack01State.h"
#include "PlayerMotion/Attack02State.h"
#include "PlayerMotion/../../Stage/Stage.h"
#include "../Camera/FollowCamera.h"

class Player : public Object3D
{
	friend RunState;
	friend Attack01State;
	friend Attack02State;
public:
	Player(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_),
		m_Model(nullptr),
		m_Speed(2.f),
		m_IsMove(false),
		m_OldPos(m_Pos),
		m_Angle(0.f),
		m_State(nullptr),
		m_Stage(nullptr),
		m_Camera(nullptr),
		m_Velocity{ 0.f,0.f,0.f },
		m_OldVelocity{ 0.f,0.f,0.f }
	{
		Init();
	}
	~Player(){}

	
	void Update()override;
	void Draw()override;

	void SetMotion(std::string keyword) { m_Model->Play(keyword); }

private:
	void Init() override;
	void Release()override;

	void Attack();
	void Move(float x_, float z_);

private:
	
	bool m_IsMove;
	float m_Speed;
	DirectX::XMFLOAT3 m_OldPos;
	DirectX::XMFLOAT3 m_Velocity;
	DirectX::XMFLOAT3 m_OldVelocity;
	float m_Angle;
	PlayerState* m_State;
	FbxModel* m_Model;

	Stage* m_Stage;
	FollowCamera* m_Camera;

};

#endif