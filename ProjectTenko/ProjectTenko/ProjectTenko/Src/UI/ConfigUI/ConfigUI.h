#ifndef CONFIGUI_H_
#define CONFIGUI_H_

#include "../UI.h"

enum CONFIG_UI_LIST
{
	CONFIG_UI_CONFIG,
	CONFIG_UI_MOUSE_NORMAL,
	CONFIG_UI_MOUSE_REVERSE,
	CONFIG_UI_RETURN,

	CONFIG_UI_MAX,
};

class ConfigUI : public UI
{
public:
	ConfigUI();
	~ConfigUI();

	void Update();

	void Draw();

	bool IsSelect(CONFIG_UI_LIST id_);

private:
	UI_PARAMETER m_ConfigUIList[CONFIG_UI_LIST::CONFIG_UI_MAX];

};

#endif