#include "GameClearUI.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Texture/Texture.h"

int Scast(GAMECLEAR_UI_LIST param_) { return static_cast<int>(param_); }

GameClearUI::GameClearUI()
{
	IsLit = true;
	m_GameClearUIList[Scast(GAMECLEAR_UI_LIST::GAMECLEAR_BACKGROUND)] = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f), 1920.f, 1080.f, "assets/UI/gameclear/clear01.png");
	m_GameClearUIList[Scast(GAMECLEAR_UI_LIST::GAMECLEAR_UI_RETURN)]  = UI_PARAMETER(D3DXVECTOR2(1100.f, 1000.f), 1024.0f, 64.f, "assets/UI/gameclear/clear02.png");
}

void GameClearUI::Update()
{
	static int lit_timer;
	lit_timer++;
	
	// 30フレームごとに点滅させつ
	if (lit_timer % 30 == 0)
	{
		IsLit = !IsLit;
	}

}

void GameClearUI::Draw()
{
	for (int i = 0; i < Scast(GAMECLEAR_UI_LIST::GAMECLEAR_UI_MAX); ++i)
	{
		// もし点灯していなかったら描画しない
		if (i == Scast(GAMECLEAR_UI_LIST::GAMECLEAR_UI_RETURN) && !IsLit) continue;
		THE_TEXTUREMANAGER->DrawTexture(m_GameClearUIList[i].m_Pos.x, m_GameClearUIList[i].m_Pos.y, m_GameClearUIList[i].m_TexturHandleKey);
	}
}

bool GameClearUI::IsSelect(GAMECLEAR_UI_LIST id_)
{
	int ui_width  = m_GameClearUIList[Scast(id_)].m_SpriteWidth;
	int ui_height = m_GameClearUIList[Scast(id_)].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_GameClearUIList[Scast(id_)].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}