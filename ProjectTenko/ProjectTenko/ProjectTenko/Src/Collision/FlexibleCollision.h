#ifndef FLEXIBLECOLLISION_H_
#define FLEXIBLECOLLISION_H_

#include "Collision.h"
#include "Shape/Shape.h"
#include <vector>

class Shape;

/**
* @brief 当たり判定管理クラス
*/
class FlexibleCollision
{
public:
	/**
	* @brief コンストラクタ
	*/
	FlexibleCollision();
	
	/**
	* @brief デストラクタ
	*/
	~FlexibleCollision();

	/**
	* @brief	 当たり判定を行う関数
	* @param[in] s1_	当たり判定を行うグループ
	* @param[in] s2_	当たり判定を行うグループ
	* @return bool true: 当たった false: 当たっていない
	*/
	bool Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_);

	/**
	* @brief	 当たり判定を行う関数
	* @param[in] s1_	当たり判定を行うオブジェクト
	* @param[in] s2_	当たり判定を行うオブジェクト
	* @return bool true: 当たった false: 当たっていない
	*/
	bool Test(const Shape& s1_, const Shape& s2_);


private:
	//! 当たりテーブル
	Collision* m_CollisionTable[static_cast<int>(SHAPE_TYPE::Shape_Type_Num)][static_cast<int>(SHAPE_TYPE::Shape_Type_Num)];
};

#endif