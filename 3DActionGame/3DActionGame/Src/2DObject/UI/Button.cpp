#include "Button.h"
#include "../../Engine/InputManager.h"
#include "../../Utility/Calculation.h"

void Button::Update()
{
	POINT mouse_pos = InputManager::GetInstance()->GetMousePos();
	m_IsHover = Calculation::HitRectAndPoint(m_Rect, static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

	if (m_IsHover && InputManager::GetInstance()->GetMouseDown(MouseButton::Left))
	{
		m_PushedFunc();
	}
}

void Button::Draw()
{
	if (m_IsHover)
	{
		TextureManager::GetInstance()->Render(m_Hover, m_Pos);
	}
	else
	{
		TextureManager::GetInstance()->Render(m_Normal, m_Pos);
	}
}

void Button::Init()
{
}

void Button::Release()
{
}
