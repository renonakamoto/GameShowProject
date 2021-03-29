#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "PlayerMotion/PlayerState.h"

class Player : public Object3D
{
public:
	Player() :
		m_Model(nullptr),
		m_Speed(2.f),
		m_IsMove(false),
		m_OldPos(m_Pos),
		m_Angle(0.f)
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
	void UpdateMotion();

private:
	
	bool m_IsMove;
	float m_Speed;
	DirectX::XMFLOAT3 m_OldPos;
	float m_Angle;
	
	bool m_Attacking;
	bool m_Attacking2;
	int  m_AttackFlameCount;

	FbxModel* m_Model;

};

#endif