#ifndef UI_H_
#define UI_H_

#include <string>
#include <d3dx9.h>

class UI
{
public:
	UI(D3DXVECTOR2 pos_, std::string texHandle_):
		m_Pos(pos_),
		m_TexturHandleKey(texHandle_)
	{}

	virtual ~UI(){}

	virtual void Update() = 0;

	virtual void Draw() = 0;
	
	//!	UIが選択されたかどうかを返す関数
	virtual bool IsSelect() { return false; }

protected:
	D3DXVECTOR2 m_Pos;

	std::string m_TexturHandleKey;
	
};

#endif