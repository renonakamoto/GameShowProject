#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "../ObjectManager/Object3D.h"

/**
* @brief ゲームオブジェクトの当たり判定を管理するクラス
*/
class CollisionManager
{
public:
	/**
	* @fn static CollisionManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return CollisionManager* インスタンスのポインタ
	*/
	static CollisionManager* GetInstance()
	{
		static CollisionManager instance;
		return &instance;
	}

public:
	/**
	* @fn void Register(Object3D* object_)
	* @brief 当たり判定リストに追加する関数
	* @param[in] object_ 3Dオブジェクト
	* @details m_Shapeにシェイプを設定していないと登録されない
	*/
	void Register(Object3D* object_);

	/**
	* @fn bool CheckHitObject(Shape3D& shape_, Object3D* hitObject_)
	* @brief リストに登録されているオブジェクトと当たっているかを判定する関数
	* @param[in] shape_ 形状
	* @param[out] hitObject_ 当たってるオブジェクトのポインタ
	* @return bool 当たっているかどうかを真偽で返す
	* @details 初めに当たったオブジェクトのポインタを返す
	*/
	bool CheckHitObject(Shape3D& shape_, Object3D* hitObject_);

	/**
	* @fn bool CheckHitObjects(Shape3D& shape_, std::vector<Object3D*>* hitObjects_)
	* @brief リストに登録されているオブジェクトと当たっているかを判定する関数
	* @param[in] shape_ 形状
	* @param[out] hitObjects_ 当たってるオブジェクトのポインタリスト
	* @return bool 当たっているかどうかを真偽で返す
	* @details 当たっているオブジェクトすべてをvectorに格納して返す
	*/
	bool CheckHitObjects(Shape3D& shape_, std::vector<Object3D*>* hitObjects_);

	/**
	* @fn void Release(Object3D* object_)
	* @brief リストから指定したオブジェクトを削除する関数
	* @param[in] object_ 削除したいオブジェクト
	* @details deleteはしない
	*/
	void Release(Object3D* object_);

	/**
	* @fn void AllRelease()
	* @brief リストに登録されているオブジェクトをすべて削除する関数
	* @details deleteはしない
	*/
	void AllRelease();

private:
	/**
	* @brief コンストラクタ
	*/
	CollisionManager() 
	{}

	/**
	* @brief デストラクタ
	*/
	~CollisionManager()
	{
		AllRelease();
	}

private:
	std::vector<Object3D*> m_Collision3DList;	//! コリジョンリスト

};

#endif