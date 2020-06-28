#ifndef GAMECLEARUI_H_
#define GAMECLEARUI_H_

#include "../UI.h"

enum GAMECLEAR_UI_LIST
{
	GAMECLEAR_BACKGROUND,
	GAMECLEAR_UI_RETURN,

	GAMECLEAR_UI_MAX,
};

class GameClearUI : public UI
{
public:
	GameClearUI();
	~GameClearUI() {}

	void Update();

	void Draw();

	bool IsSelect(GAMECLEAR_UI_LIST id_);

private:
	UI_PARAMETER m_TitleUIList[GAMECLEAR_UI_LIST::GAMECLEAR_UI_MAX];

	bool IsLit;
};

#endif