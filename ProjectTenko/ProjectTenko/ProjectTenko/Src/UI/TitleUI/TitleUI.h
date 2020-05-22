#ifndef TITLEUI_H_
#define TITLEUI_H_

#include "../UI.h"

enum UI_LIST
{
	UI_START,
	UI_END,


	UI_MAX,
};

class TitleUI
{
public:
	TitleUI();
	~TitleUI();

	void Update();

	void Draw();

private:
	UI* m_TitleUIList[UI_MAX];
};

#endif