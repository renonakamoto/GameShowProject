#include "Button.h"
#include "../../Engine/Engine.h"
#include "../../Utility/Calculation.h"

void Button::Update()
{
	POINT mouse_pos = INPUT->GetMousePos();
	m_IsHover = Calculation::HitRectAndPoint(m_Rect, static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

	if (m_IsHover && INPUT->GetMouseDown(MouseButton::Left))
	{
		m_PushedFunc();
	}
}

void Button::Draw()
{
	if (m_IsHover)
	{
		TEX_MANAGER->Render(m_Hover, m_Pos);
	}
	else
	{
		TEX_MANAGER->Render(m_Normal, m_Pos);
	}
}