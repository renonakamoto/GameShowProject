#ifndef VEC2I_H_
#define VEC2I_H_

/**
* @brief int型のベクトルを扱う構造体
*/
struct Vec2I
{
	int X;	//! X成分
	int Y;	//! Y成分

	/**
	* @brief コンストラクタ
	*/
	Vec2I() :
		Vec2I(0, 0)
	{}

	/**
	* @brief コンストラクタ
	* @param[in] x_ X成分
	* @param[in] y_ Y成分
	*/
	Vec2I(int x_, int y_) :
		X(x_), Y(y_)
	{}
	

	
	bool operator == (Vec2I v) { return ((X == v.X) && (Y == v.Y)); }
	bool operator != (Vec2I v) { return ((X != v.X) || (Y != v.Y)); }
};

#endif