#include "StartUI.h"
#include "../../Engine/Texture/Texture.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"

void StartUI::Update()
{
}

void StartUI::Draw()
{
	THE_TEXTUREMANAGER->DrawTexture(m_Pos.x, m_Pos.y, m_TexturHandleKey);
}

bool StartUI::IsSelect()
{
	int ui_width  = THE_TEXTUREMANAGER->GetTexturue(m_TexturHandleKey)->width;
	int ui_height = THE_TEXTUREMANAGER->GetTexturue(m_TexturHandleKey)->height;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
