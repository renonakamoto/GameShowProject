#include "DebugManager.h"
#include "../Engine/Input/InputManager.h"
#include "../Engine/Font/Font.h"

void DebugManager::Update()
{
	if (THE_INPUTMANAGER->GetKey(KeyInfo::Key_X))
	{
		if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_Down))
		{
			m_MouseSensivity -= 1.0f;

			if (m_MouseSensivity < 20.0f) m_MouseSensivity = 20.0f;
		}

		if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_Up))
		{
			m_MouseSensivity += 1.0f;
		}
	}
	

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_M))
	{
		m_IsSimpleMap = !m_IsSimpleMap;
	}
	
	
}

void DebugManager::Draw()
{
	THE_FONT->DrawFont(1000.0f, 480.0f, "Press X + Up or Down");
	std::string mouse_sensi = "MouseSensivity : " + std::to_string(m_MouseSensivity);
	THE_FONT->DrawFont(1000.0f, 500.0f, mouse_sensi);

	THE_FONT->DrawFont(1000.0f, 540.0f, "Press M");
	if (m_IsSimpleMap) THE_FONT->DrawFont(1000.0f, 560.0f, "簡易版マップ");
	else THE_FONT->DrawFont(1000.0f, 560.0f, "通常マップ");

}
