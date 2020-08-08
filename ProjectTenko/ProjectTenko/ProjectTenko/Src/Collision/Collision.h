#ifndef COLLISION_H_
#define COLLISION_H_

class Shape;
class AABBShape;
class CylinderShape;
class Ray;

/**
* @brief	 当たり判定基底クラス
*/
class Collision
{
public:
	virtual ~Collision() {}

	virtual bool Test(const Shape* s1_, const Shape* s2_) = 0;
};

/**
* @brief	AABB同士の当たり判定を行うクラス
* @details	FlexibleCollitionで管理している
*/
class AABBAndAABB : public Collision
{
public:
	AABBAndAABB() {}
	virtual ~AABBAndAABB() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;

};

/**
* @brief	AABBと円柱との当たり判定を行うクラス
* @details	FlexibleCollitionで管理しているため触る必要はない
*/
class AABBAndCylinder : public Collision
{
public:
	AABBAndCylinder() {}
	virtual ~AABBAndCylinder() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

/**
* @brief	AABBとレイとの当たり判定を行うクラス
* @details	FlexibleCollitionで管理しているため触る必要はない
*/
class AABBandRay : public Collision
{
public:
	AABBandRay(){}
	virtual ~AABBandRay() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

/**
* @brief	円柱とレイとの当たり判定を行うクラス
* @details	FlexibleCollitionで管理しているため触る必要はない
*/
class CylinderAndRay : public Collision
{
public:
	CylinderAndRay(){}
	virtual ~CylinderAndRay(){}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

#endif