#ifndef COLLISION_H_
#define COLLISION_H_

class Shape;
class AABBShape;
class CylinderShape;
class Ray;

//! “–‚½‚è”»’è‚ÌŠî’êƒNƒ‰ƒX
class Collision
{
public:
	virtual ~Collision() {}

	virtual bool Test(const Shape& s1, const Shape& s2) = 0;
};

class AABBAndAABB : public Collision
{
public:
	AABBAndAABB() {}
	virtual ~AABBAndAABB() {}

	bool Test(const Shape& s1, const Shape& s2) override;

};

class AABBandCylinder : public Collision
{
public:
	AABBandCylinder() {}
	virtual ~AABBandCylinder() {}

	bool Test(const Shape& s1, const Shape& s2);
};

class AABBandRay : public Collision
{
public:
	AABBandRay(){}
	virtual ~AABBandRay() {}

	bool Test(const Shape& s1, const Shape& s2);

};

class CylinderAndRay : public Collision
{
public:
	CylinderAndRay(){}
	virtual ~CylinderAndRay(){}

	bool Test(const Shape& s1, const Shape& s2);

};

#endif