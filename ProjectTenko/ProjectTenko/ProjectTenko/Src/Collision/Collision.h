#ifndef COLLISION_H_
#define COLLISION_H_

class Shape;
class AABBShape;
class CylinderShape;
class Ray;

/**
* @brief	 �����蔻����N���X
*/
class Collision
{
public:
	virtual ~Collision() {}

	virtual bool Test(const Shape* s1_, const Shape* s2_) = 0;
};

/**
* @brief	AABB���m�̓����蔻����s���N���X
* @details	FlexibleCollition�ŊǗ����Ă���
*/
class AABBAndAABB : public Collision
{
public:
	AABBAndAABB() {}
	virtual ~AABBAndAABB() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;

};

/**
* @brief	AABB�Ɖ~���Ƃ̓����蔻����s���N���X
* @details	FlexibleCollition�ŊǗ����Ă��邽�ߐG��K�v�͂Ȃ�
*/
class AABBAndCylinder : public Collision
{
public:
	AABBAndCylinder() {}
	virtual ~AABBAndCylinder() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

/**
* @brief	AABB�ƃ��C�Ƃ̓����蔻����s���N���X
* @details	FlexibleCollition�ŊǗ����Ă��邽�ߐG��K�v�͂Ȃ�
*/
class AABBandRay : public Collision
{
public:
	AABBandRay(){}
	virtual ~AABBandRay() {}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

/**
* @brief	�~���ƃ��C�Ƃ̓����蔻����s���N���X
* @details	FlexibleCollition�ŊǗ����Ă��邽�ߐG��K�v�͂Ȃ�
*/
class CylinderAndRay : public Collision
{
public:
	CylinderAndRay(){}
	virtual ~CylinderAndRay(){}

	bool Test(const Shape* s1_, const Shape* s2_) override;
};

#endif