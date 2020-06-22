#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Utility/SingletonTemplate.h"
#include "../../Src/ObjectBase/ObjectBase.h"
#include "../Camera/Camera.h"
#include "../Collision/FlexibleCollision.h"
#include "../ObjectBase/MapObject/MapDataBank.h"
#include <vector>
#include <iostream>
#include <memory>

class Objectmanager
{

	friend MySingletonTemplate::SingletonTemplate<Objectmanager>;
public:
	
	/**
	* @brief オブジェクトの更新関数
	*/
	void Update();

	/**
	* @brief オブジェクトの描画関数）
	*/
	void Draw();

	/**
	* @brief プレイヤーとマップ障害物との当たり判定関数
	* @return bool 当たった:true 当たっていない:false
	*/
	bool HitPlayerAndMapObject();

	/**
	* @brief プレイヤーとエネミーとの当たり判定関数
	* @return bool 当たった:true 当たっていない:false
	*/
	bool HitPlayerAndEnemy();

	/**
	* @brief カメラとマップ障害物との当たり判定関数
	* @return bool 当たった:true 当たっていない:false
	*/
	bool HitCameraAndObject();

	/**
	* @brief プレイヤーとクリアトリガーとの当たり判定関数
	* @return bool 当たった:true 当たっていない:false
	*/
	bool HitPlayerAndClearTrigger();

	/**
	* @brief レイとオブジェクトとの当たり判定
	* @param[in] origin_ レイの原点
	* @param[in] delta_  レイの向きと大きさ(ベクトル)
	* @return bool 成功:true 失敗:false
	*/
	bool HitRayAndObject(const D3DXVECTOR3& origin_, const D3DXVECTOR3& delta_);



	Camera* GetCameraInstance()const {
		if (!m_Camera) { return nullptr; }
		return m_Camera;
	}

	void AllRelease();

private:
	Objectmanager();
	~Objectmanager();

	/*
		当たり判定を行うオブジェクトを算出する関数
	*/
	void JudgementCollition(std::vector<Shape*>* pOut_, const D3DXVECTOR3& basePoint_, float length);
	

	ObjectBase* m_Player;
	std::vector<ObjectBase*> m_Object;
	std::vector<ObjectBase*> m_EnemyGroup;
	std::vector<ObjectBase*> m_MapObjectGroup;

	Camera* m_Camera;

	FlexibleCollision m_Collision;
	MapDataBank m_MapDataBank;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif