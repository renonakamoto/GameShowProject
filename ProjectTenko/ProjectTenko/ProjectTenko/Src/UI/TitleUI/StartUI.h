#ifndef STARTUI_H_
#define STARTUI_H_

#include "../UI.h"

class StartUI : public UI
{
public:
	StartUI(D3DXVECTOR2 pos_, std::string texHandle_) :
		UI(pos_, texHandle_)
	{}

	virtual ~StartUI() {}

	virtual void Update() override;

	virtual void Draw() override;

	//!	UI‚ª‘I‘ğ‚³‚ê‚½‚©‚Ç‚¤‚©‚ğ•Ô‚·ŠÖ”
	virtual bool IsSelect() override;

private:

};

#endif