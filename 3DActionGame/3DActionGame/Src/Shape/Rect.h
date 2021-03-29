#ifndef RECT_H_
#define RECT_H_

struct Rect
{
	float m_Top;
	float m_Bottom;
	float m_Left;
	float m_Right;

	Rect() :
		Rect(0.f, 0.f, 0.f, 0.f)
	{}

	Rect(float top_, float bottom_, float left_, float right) :
		m_Top(top_),
		m_Bottom(bottom_),
		m_Left(left_),
		m_Right(right)
	{}
};

#endif