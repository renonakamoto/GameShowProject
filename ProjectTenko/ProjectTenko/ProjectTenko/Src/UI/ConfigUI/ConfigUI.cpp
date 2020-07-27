#include "ConfigUI.h"
#include "../../Engine/Texture/Texture.h"
#include "../../Utility/SimpleCollision.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Manager/ConfigManager.h"
#include "../../Utility/SimpleCalculation.h"

int Scast(CONFIG_UI_LIST param_) { return static_cast<int>(param_); }

ConfigUI::ConfigUI()
{
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_CONFIG)]					 = UI_PARAMETER(D3DXVECTOR2(0.f, 0.f),    1920.f, 1080.f, "assets/UI/config/config01.png");
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL)]			 = UI_PARAMETER(D3DXVECTOR2(680.f, 320.f), 256.f,  128.f,  "assets/UI/config/config02.png");
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE)]			 = UI_PARAMETER(D3DXVECTOR2(1000.f, 320.f), 256.f,  128.f,  "assets/UI/config/config03.png");
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_NORMAL)]	 = UI_PARAMETER(D3DXVECTOR2(680.f, 320.f), 256.f,  128.f,  "assets/UI/config/config05.png");
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_REVERSE)] = UI_PARAMETER(D3DXVECTOR2(1000.f, 320.f), 256.f,  128.f,  "assets/UI/config/config06.png");
	m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_RETURN)]					 = UI_PARAMETER(D3DXVECTOR2(840.f, 930.f), 256.f, 128.f,  "assets/UI/config/config04.png");
}

ConfigUI::~ConfigUI()
{
}

void ConfigUI::Update()
{
	if (THE_INPUTMANAGER->GetMouseDown(MouseButton::Left) == false) { return; }

	// ‚à‚µ’Êíƒ}ƒEƒXUI‚ª‰Ÿ‚³‚ê‚½‚ç”½“]‚µ‚È‚¢
	if (IsSelect(CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL))
	{
		THE_CONFIGMANAGER->SetMouseFlip(false);

	}// ‚à‚µ”½“]ƒ}ƒEƒXUI‚ª‰Ÿ‚³‚ê‚½‚ç”½“]‚·‚é
	else if (IsSelect(CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE))
	{
		THE_CONFIGMANAGER->SetMouseFlip(true);
	}
}

void ConfigUI::Draw()
{
	THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_CONFIG)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_CONFIG)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_CONFIG)].m_TexturHandleKey);
	THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_RETURN)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_RETURN)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_RETURN)].m_TexturHandleKey);

	if (THE_CONFIGMANAGER->IsMouseFlip())
	{
		THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_REVERSE)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_REVERSE)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_REVERSE)].m_TexturHandleKey);
		THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_NORMAL)].m_TexturHandleKey);
	}
	else
	{
		THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_NORMAL)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_NORMAL)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_SELECTING_MOUSE_NORMAL)].m_TexturHandleKey);
		THE_TEXTUREMANAGER->DrawTexture(m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE)].m_Pos.x, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE)].m_Pos.y, m_ConfigUIList[Scast(CONFIG_UI_LIST::CONFIG_UI_MOUSE_REVERSE)].m_TexturHandleKey);
	}
}

bool ConfigUI::IsSelect(CONFIG_UI_LIST id_)
{
	int ui_width  = m_ConfigUIList[Scast(id_)].m_SpriteWidth;
	int ui_height = m_ConfigUIList[Scast(id_)].m_SpriteHeight;

	D3DXVECTOR2 mouse_pos = D3DXVECTOR2(THE_INPUTMANAGER->GetMousePos().x, THE_INPUTMANAGER->GetMousePos().y);

	if (SimpleCollision::HitRectAndPoint(m_ConfigUIList[Scast(id_)].m_Pos, ui_width, ui_height, mouse_pos) == true)
	{
		return true;
	}

	return false;
}
