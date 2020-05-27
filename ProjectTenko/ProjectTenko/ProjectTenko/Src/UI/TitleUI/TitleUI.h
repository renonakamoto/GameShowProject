#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "../UI.h"


enum TITLE_UI_LIST
{
	TITLE_UI_TITLE,
	TITLE_UI_START,
	TITLE_UI_EXIT,
	TITLE_UI_SETTING,

	TITLE_UI_MAX,
};

class TitleUI : public UI
{
public:
	TitleUI();
	~TitleUI();

	void Update();

	void Draw();

	bool IsSelect(TITLE_UI_LIST id_);

private:
	UI_PARAMETER m_TitleUIList[TITLE_UI_LIST::TITLE_UI_MAX];

};

#endif