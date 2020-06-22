#include "GameClearUI.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Texture/Texture.h"

GameClearUI::GameClearUI()
{
	IsLit = true;
	m_TitleUIList[GAMECLEAR_UI_LIST::GAMECLEAR_BACKGROUND] = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f), 1920.f, 1080.f, "assets/UI/gameclear/clear01.png");
	m_TitleUIList[GAMECLEAR_UI_LIST::GAMECLEAR_UI_RETURN]  = UI_PARAMETER(D3DXVECTOR2(1100.f, 1000.f), 1024.0f, 64.f, "assets/UI/gameclear/clear02.png");
}

void GameClearUI::Update()
{
	static int lit_timer;
	lit_timer++;

	if (lit_timer % 30 == 0)
	{
		IsLit = !IsLit;
	}

}

void GameClearUI::Draw()
{
	for (int i = 0; i < GAMECLEAR_UI_LIST::GAMECLEAR_UI_MAX; ++i)
	{
		if (i == GAMECLEAR_UI_LIST::GAMECLEAR_UI_RETURN && !IsLit) continue;
		THE_TEXTUREMANAGER->DrawTexture(m_TitleUIList[i].m_Pos.x, m_TitleUIList[i].m_Pos.y, m_TitleUIList[i].m_TexturHandleKey);
	}
}

bool GameClearUI::IsSelect(GAMECLEAR_UI_LIST id_)
{
	int ui_width  = m_TitleUIList[id_].m_SpriteWidth;
	int ui_height = m_TitleUIList[id_].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_TitleUIList[id_].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}