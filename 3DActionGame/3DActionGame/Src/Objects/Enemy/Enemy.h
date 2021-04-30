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
class Enemy : public ShadowMapObject
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
		ShadowMapObject(pos_, { 0.f, 0.f, 0.f }, { 0.1f, 0.1f, 0.1f }),
		m_Model(nullptr),
		m_Stage(nullptr),
		m_State(nullptr),
		m_Hp(10),
		m_IsHit(false),
		m_IsDeath(false),
		m_EnemySize(30.f, 40.f, 22.f)
	{
		m_Tag = "Enemy";
	}
	
	/**
	* @brief デストラクタ
	*/
	~Enemy() final
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
	* @fn void Damage(int damageNum_)
	* @brief エネミーのHPを減らす関数
	* @param[in] damageNum_ エネミーが受けるダメージ数
	* @details HPが0以下になったら死亡する
	*/
	void Damage(int damageNum_);

	/**
	* @fn bool IsDeath()
	* @brief 死亡フラグ取得関数
	* @return bool true:死亡  false:生存
	*/
	bool IsDeath() { return m_IsDeath; }

private:
	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release()override;

private:
	std::unique_ptr<SkeletalModel> m_Model;		//! モデル
	EnemyState*					   m_State;		//! ステートクラス
	int							   m_Hp;		//! ヒットポイント
	bool						   m_IsHit;		//! 攻撃をくらったかどうか
	bool						   m_IsDeath;	//! 死んでいるかどうか
	DirectX::XMFLOAT3			   m_EnemySize; //! エネミーの大きさ

	Stage*						   m_Stage;		//! ステージの参照用変数
};

#endif
