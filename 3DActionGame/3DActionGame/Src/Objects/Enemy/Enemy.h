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

/**
* @brief 敵クラス
*/
class Enemy : public Object3D
{
	friend EnemyIdleState;
	friend EnemyHitState;
	friend EnemyDeathState;

public:
	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	Enemy(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_),
		m_Model(nullptr),
		m_Stage(nullptr),
		m_State(nullptr),
		m_Hp(10),
		m_IsHit(false),
		m_IsDeath(false)
	{}
	
	/**
	* @brief デストラクタ
	*/
	~Enemy()
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
	* @fn void Damage(int damageNum_)
	* @brief エネミーのHPを減らす関数
	* @param[in] damageNum_ エネミーが受けるダメージ数
	* @details HPが0以下になったらm_IsDeathがtrueになる
	*/
	void Damage(int damageNum_);

private:
	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release()override;

private:
	SkeletalModel* m_Model;	//! モデル
	EnemyState* m_State;	//! ステートクラス
	int m_Hp;				//! ヒットポイント
	bool m_IsHit;			//! 攻撃をくらったかどうか
	bool m_IsDeath;			//! 死んでいるかどうか

	Stage* m_Stage;			//! ステージの参照用変数
};

#endif
