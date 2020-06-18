#ifndef POSEUI_H_
#define POSEUI_H_

#include "../UI.h"

enum PAUSE_UI_LIST
{
	PAUSE_UI_BACKGROUND,
	PAUSE_UI_RETURN_GAME,
	PAUSE_UI_RETURN_TITLE,
	PAUSE_UI_SETTING,

	PAUSE_UI_MAX,
};

class PauseUI : public UI
{
public:
	PauseUI();
	~PauseUI();

	void Update();

	void Draw();

	bool IsSelect(PAUSE_UI_LIST id_);

private:
	UI_PARAMETER m_PoseUIList[PAUSE_UI_LIST::PAUSE_UI_MAX];

};

#endif