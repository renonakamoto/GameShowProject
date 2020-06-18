#include "GameOverUI.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Texture/Texture.h"

GameOverUI::GameOverUI()
{
	m_TitleUIList[GAMEOVER_UI_LIST::GAMEOVER_BACKGROUND] = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f), 1920.f, 1080.f, "assets/UI/gameover/gameover01.png");
	m_TitleUIList[GAMEOVER_UI_LIST::GAMEOVER_UI_RETURN]  = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f), 1024.f, 128.f,  "assets/UI/gameover/gameover03.png");

}
void GameOverUI::Update()
{
}

void GameOverUI::Draw()
{
	for (int i = 0; i < GAMEOVER_UI_LIST::GAMEOVER_UI_MAX; ++i)
	{
		THE_TEXTUREMANAGER->DrawTexture(m_TitleUIList[i].m_Pos.x, m_TitleUIList[i].m_Pos.y, m_TitleUIList[i].m_TexturHandleKey);
	}
}

bool GameOverUI::IsSelect(GAMEOVER_UI_LIST id_)
{
	int ui_width = m_TitleUIList[id_].m_SpriteWidth;
	int ui_height = m_TitleUIList[id_].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_TitleUIList[id_].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
