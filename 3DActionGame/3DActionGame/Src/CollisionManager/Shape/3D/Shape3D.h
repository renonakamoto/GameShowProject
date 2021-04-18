#ifndef SHAPE_3D_H_
#define SHAPE_3D_H_

class ShapeOBB;

/**
* @brief 3Dの形状基底クラス
*/
class Shape3D
{
public:
	/**
	* @fn bool HitTest(Shape3D& shape_)
	* @brief 引数の形状と当たり判定を行う関数
	* @param[in] shape_ 形状
	* @return bool 当たっているかどうかを真偽で返す
	* @details ダブルディスパッチで形状を特定して、当たり判定を行う
	*/
	virtual bool HitTest(Shape3D& shape_) = 0;

	/**
	* @fn bool HitTest(ShapeOBB& shape_)
	* @brief OBBとの当たり判定を行う関数
	* @param[in] shape_ OBB
	* @return bool 当たっているかどうかを真偽で返す
	* @details 派生先で当たり判定の処理を実装する
	*/
	virtual bool HitTest(ShapeOBB& shape_) = 0;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details 派生先で形状の描画を行う
	*/
	virtual void Draw(){}
};

#endif