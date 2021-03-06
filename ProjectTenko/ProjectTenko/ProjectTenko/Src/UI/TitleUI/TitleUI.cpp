#include "TitleUI.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Texture/Texture.h"

int Scast(TITLE_UI_LIST param_) { return static_cast<int>(param_); }

TitleUI::TitleUI()
{
	m_TitleUIList[Scast(TITLE_UI_LIST::TITLE_UI_TITLE)]   = UI_PARAMETER(D3DXVECTOR2(0.0f,   0.0f ), 1024.f, 256.f, "assets/UI/title/title01.png");
	m_TitleUIList[Scast(TITLE_UI_LIST::TITLE_UI_START)]   = UI_PARAMETER(D3DXVECTOR2(704.0f, 640.f), 512.f,  64.f,  "assets/UI/title/title02.png");
	m_TitleUIList[Scast(TITLE_UI_LIST::TITLE_UI_SETTING)] = UI_PARAMETER(D3DXVECTOR2(704.0f, 740.f), 512.f,  64.f,  "assets/UI/title/title04.png");
	m_TitleUIList[Scast(TITLE_UI_LIST::TITLE_UI_EXIT)]    = UI_PARAMETER(D3DXVECTOR2(704.0f, 840.f), 512.f,  64.f,  "assets/UI/title/title05.png");

}

TitleUI::~TitleUI()
{
}

void TitleUI::Update()
{
}

void TitleUI::Draw()
{
	for (int i = 0; i < Scast(TITLE_UI_LIST::TITLE_UI_MAX); ++i)
	{
		THE_TEXTUREMANAGER->DrawTexture(m_TitleUIList[i].m_Pos.x, m_TitleUIList[i].m_Pos.y, m_TitleUIList[i].m_TexturHandleKey);
	}
}

bool TitleUI::IsSelect(TITLE_UI_LIST id_)
{
	int ui_width  = m_TitleUIList[Scast(id_)].m_SpriteWidth;
	int ui_height = m_TitleUIList[Scast(id_)].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_TitleUIList[Scast(id_)].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
