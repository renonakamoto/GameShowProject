#ifndef UI_H_
#define UI_H_

#include <string>
#include <d3dx9.h>

class UI
{
public:
	UI()
	{}

	virtual ~UI(){}

	virtual void Update() = 0;

	virtual void Draw() = 0;

protected:
	struct UI_PARAMETER
	{
		UI_PARAMETER(){}
		UI_PARAMETER(D3DXVECTOR2 pos_, float spriteWidth_, float spriteHeight, std::string texHandleKey):
			m_Pos(pos_),
			m_SpriteWidth(spriteWidth_),
			m_SpriteHeight(spriteHeight),
			m_TexturHandleKey(texHandleKey)
		{}

		D3DXVECTOR2 m_Pos;
		float m_SpriteWidth;
		float m_SpriteHeight;

		std::string m_TexturHandleKey;
	};
	
};

#endif