#ifndef TIKUWATEN_H_
#define TIKUWATEN_H_

#include "../EnemyBase.h"

enum class ChikuwaMotionList : unsigned char
{
	Wait,
	Walk,
	Sprint,
	ChangeDirection,
};

class Tikuwaten : public Enemybase
{
public:
	/**
	* @biref コンストラクタ
	* @param[in] pos_ 初期化時の座標
	* @param[in] player_ プレイヤーのポインタ
	* @param[in] key_ FBXのキー情報
	*/
	Tikuwaten(D3DXVECTOR3 pos_, const ObjectBase* 
		player_, std::string key_);

	/**
	* @biref デストラクタ
	*/
	virtual ~Tikuwaten() {}

	/**
	* @biref 更新関数
	*/
	virtual void Update() override;
	
	/**
	* @biref 描画関数
	*/
	virtual void Draw() override;

private:
	/**
	* @biref 巡回状態の移動処理関数
	*/
	void Patrol() override;

	/**
	* @biref 巡回中の方向転換処理関数
	*/
	void Turn() override;

	/**
	* @biref プレイヤーの追跡状態処理関数
	*/
	void Chase() override;

	/**
	* @biref 巡回経路に復帰する際の移動処理関数
	*/
	void Return() override;
	
	/**
	* @biref 巡回経路に復帰するための経路探索関数
	*/
	void Thinking() override;

private:
	ChikuwaMotionList		     m_CrrentMotion;	//!< 現在のモーション
	FbxMotion<ChikuwaMotionList> m_Motion;			//!< モーションリスト
};

#endif