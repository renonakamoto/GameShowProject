#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "../../Model/SkeletalModel.h"
#include "../Stage/Stage.h"

#include "EnemyState/EnemyState.h"
#include "EnemyState/EnemyIdleState.h"
#include "EnemyState/EnemyHitState.h"
#include "EnemyState/EnemyDeathState.h"

class Enemy : public Object3D
{
	friend EnemyIdleState;
	friend EnemyHitState;
	friend EnemyDeathState;

public:
	Enemy(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_),
		m_Model(nullptr),
		m_Stage(nullptr),
		m_State(nullptr),
		m_Hp(10),
		m_IsHit(false),
		m_IsDeath(false)
	{}

	~Enemy()
	{
		Release();
	}

	void Init() override;
	void Update()override;
	void Draw()override;

	void Damage(int damageNum_);

private:
	void Release()override;

private:
	SkeletalModel* m_Model;
	
	Stage* m_Stage;
	EnemyState* m_State;
	
	int m_Hp;			//! ヒットポイント
	bool m_IsHit;		//! 攻撃をくらったかどうか
	bool m_IsDeath;
};

#endif
