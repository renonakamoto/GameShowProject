#include "PauseUI.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Texture/Texture.h"

PauseUI::PauseUI()
{
	m_PoseUIList[PAUSE_UI_LIST::PAUSE_UI_BACKGROUND]   = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f),	 1920.f, 1080.f, "assets/UI/pause/pause01.png");
	m_PoseUIList[PAUSE_UI_LIST::PAUSE_UI_SETTING]	   = UI_PARAMETER(D3DXVECTOR2(450.f, 340.f), 1024.f, 128.f, "assets/UI/pause/pause04.png");
	m_PoseUIList[PAUSE_UI_LIST::PAUSE_UI_RETURN_GAME]  = UI_PARAMETER(D3DXVECTOR2(450.f, 540.f), 1024.f, 128.f, "assets/UI/pause/pause02.png");
	m_PoseUIList[PAUSE_UI_LIST::PAUSE_UI_RETURN_TITLE] = UI_PARAMETER(D3DXVECTOR2(450.f, 740.f), 1024.f, 128.f, "assets/UI/pause/pause05.png");

}

PauseUI::~PauseUI()
{
}

void PauseUI::Update()
{
}

void PauseUI::Draw()
{
	for (int i = 0; i < PAUSE_UI_LIST::PAUSE_UI_MAX; ++i)
	{
		THE_TEXTUREMANAGER->DrawTexture(m_PoseUIList[i].m_Pos.x, m_PoseUIList[i].m_Pos.y, m_PoseUIList[i].m_TexturHandleKey);
	}
}

bool PauseUI::IsSelect(PAUSE_UI_LIST id_)
{
	int ui_width  = m_PoseUIList[id_].m_SpriteWidth;
	int ui_height = m_PoseUIList[id_].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_PoseUIList[id_].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
