#ifndef GAMEOVERUI_H_
#define GAMEOVERUI_H_

#include "../UI.h"

enum GAMEOVER_UI_LIST
{
	GAMEOVER_BACKGROUND,
	GAMEOVER_UI_RETURN,

	GAMEOVER_UI_MAX,
};

class GameOverUI : public UI
{
public:
	GameOverUI();
	~GameOverUI() {}

	void Update();

	void Draw();

	bool IsSelect(GAMEOVER_UI_LIST id_);

private:
	UI_PARAMETER m_TitleUIList[GAMEOVER_UI_LIST::GAMEOVER_UI_MAX];

};

#endif