#include "ConfigUI.h"
#include "../../Engine/Texture/Texture.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Input/InputManager.h"

ConfigUI::ConfigUI()
{
	m_ConfigUIList[CONFIG_UI_LIST::CONFIG_UI_CONFIG]		= UI_PARAMETER(D3DXVECTOR2(0.f, 0.f),    1920.f, 1080.f, "assets/UI/config/config01.png");
	m_ConfigUIList[CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL]  = UI_PARAMETER(D3DXVECTOR2(680.f, 320.f), 256.f,  128.f,  "assets/UI/config/config02.png");
	m_ConfigUIList[CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE] = UI_PARAMETER(D3DXVECTOR2(1000.f, 320.f), 256.f,  128.f,  "assets/UI/config/config03.png");
	m_ConfigUIList[CONFIG_UI_LIST::CONFIG_UI_RETURN]		= UI_PARAMETER(D3DXVECTOR2(840.f, 930.f), 256.f, 128.f,  "assets/UI/config/config04.png");

}

ConfigUI::~ConfigUI()
{
}

void ConfigUI::Update()
{
}

void ConfigUI::Draw()
{
	for (int i = 0; i < CONFIG_UI_LIST::CONFIG_UI_MAX; ++i)
	{
		THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[i].m_Pos.x, m_ConfigUIList[i].m_Pos.y, m_ConfigUIList[i].m_TexturHandleKey);
	}
}

bool ConfigUI::IsSelect(CONFIG_UI_LIST id_)
{
	int ui_width  = m_ConfigUIList[id_].m_SpriteWidth;
	int ui_height = m_ConfigUIList[id_].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_ConfigUIList[id_].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
