#ifndef RECT_H_
#define RECT_H_

/**
* @fn bool CheckHitObject(Shape3D& shape_, Object3D* hitObject_)
* @brief リストに登録されているオブジェクトと当たっているかを判定する関数
* @param[in] shape_ 形状
* @param[out] hitObject_ 当たってるオブジェクトのポインタ
* @return bool 当たっているかどうかを真偽で返す
* @details 初めに当たったオブジェクトのポインタを返す
*/
struct Rect
{
	float m_Top;		//! 上底Y
	float m_Bottom;		//! 低辺Y
	float m_Left;		//! 左辺X
	float m_Right;		//! 右辺X

	/**
	* @brief コンストラクタ
	*/
	Rect() :
		Rect(0.f, 0.f, 0.f, 0.f)
	{}

	/**
	* @brief コンストラクタ
	* @param[in] top_　   上底Y情報
	* @param[in] bottom_  低辺Y情報
	* @param[in] left_	  左辺X情報
	* @param[in] right    右辺X情報
	*/
	Rect(float top_, float bottom_, float left_, float right) :
		m_Top(top_),
		m_Bottom(bottom_),
		m_Left(left_),
		m_Right(right)
	{}
};

#endif