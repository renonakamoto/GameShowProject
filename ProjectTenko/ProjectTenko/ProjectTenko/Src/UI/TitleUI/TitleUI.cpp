#include "TitleUI.h"
#include "StartUI.h"

TitleUI::TitleUI()
{
	for (int i = 0; i < UI_MAX; ++i) m_TitleUIList[i] = nullptr;



	m_TitleUIList[UI_LIST::UI_START] = new StartUI(D3DXVECTOR2(500.f, 500.f), "assets/UI/title/Title_Start_UI.png");
}

TitleUI::~TitleUI()
{
	for (int i = 0; i < UI_MAX; ++i)
	{
		if (m_TitleUIList[i] == nullptr) continue;

		delete m_TitleUIList[i];
		m_TitleUIList[i] = nullptr;
	}
}

void TitleUI::Update()
{
	for (int i = 0; i < UI_MAX; ++i)
	{
		if (m_TitleUIList[i] == nullptr) continue;

		m_TitleUIList[i]->Update();
	}
}

void TitleUI::Draw()
{
	for (int i = 0; i < UI_MAX; ++i)
	{
		if (m_TitleUIList[i] == nullptr) {
			continue;
		}

		m_TitleUIList[i]->Draw();
	}
}
