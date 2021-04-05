#ifndef VEC2I_H_
#define VEC2I_H_

struct Vec2I
{
	int X;
	int Y;

	Vec2I() :
		Vec2I(0, 0)
	{}

	Vec2I(int x_, int y_) :
		X(x_), Y(y_)
	{}

	bool operator == (Vec2I v) { return ((X == v.X) && (Y == v.Y)); }
};

#endif