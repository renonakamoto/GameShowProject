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

/**
* @brief オブジェクト管理クラス
*/
class Objectmanager
{

	friend MySingletonTemplate::SingletonTemplate<Objectmanager>;
public:
	/**
	* @brief オブジェクトの種類列挙
	*/
	enum class ObjectType
	{
		Player,				//! プレイヤー
		Enemy,				//! エネミー
		Camera,				//! カメラ
		MapObject,			//!	マップオブジェクト

		TypeNum,			//! タイプの数
	};

public:
	
	/**
	* @brief オブジェクトの更新関数
	*/
	void Update();

	/**
	* @brief オブジェクトの描画関数）
	*/
	void Draw();
	
	void EntryObject(ObjectType type_);

	void ExitObject(ObjectType type_);

	void AllRelease();

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
		if (m_Camera == nullptr)
		{
			new Camera();
		}
		return m_Camera;
	}

private:
	/**
	* @brief コンストラクタ
	*/
	Objectmanager();

	/**
	* @brief デストラクタ
	*/
	~Objectmanager();

	/**
	* @brief 当たり判定を行うオブジェクトを算出する関数
	* @param[out] pOut_	     当たり判定を行うオブジェクト
	* @param[in] basePoint_  オブジェクトの座標
	*/
	void JudgementCollition(std::vector<Shape*>* pOut_, const D3DXVECTOR3& basePoint_, float length);

	/**
	* @brief プレイヤー生成関数
	*/
	void CreatePlayer();

	/**
	* @brief 敵生成関数
	*/
	void CreateEnemies();

	/**
	* @brief マップ生成関数
	*/
	void CreateMap();
	

	ObjectBase* m_Player;							//! プレイヤー
	std::vector<ObjectBase*> m_EnemyGroup;			//! エネミーグループ
	std::vector<ObjectBase*> m_Object;				//! 当たり判定のないオブジェクトグループ
	std::vector<ObjectBase*> m_MapObjectGroup;		//! 当たり判定のあるオブジェクトグループ

	Camera* m_Camera;	

	FlexibleCollision m_Collision;
	std::unique_ptr<MapDataBank> m_MapDataBank;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif