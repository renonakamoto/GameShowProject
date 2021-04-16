#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "../Object2D.h"
#include "../../Engine/Texture/Texture.h"
#include "../../Shape/Rect.h"

class Button : public Object2D
{
public:
	Button(std::string normal_, std::string hover_, void(*fp)(void), DirectX::XMFLOAT3 pos_):
		Object2D(pos_),
		m_Normal(normal_), 
		m_Hover(hover_),
		m_PushedFunc(fp),
		m_IsHover(false)
	{		
		TextureData* tex = TextureManager::GetInstance()->GetTexture(normal_);
		if (tex)
		{
			m_Rect.m_Top	= m_Pos.y;
			m_Rect.m_Bottom = m_Pos.y + tex->Height;
			m_Rect.m_Left	= m_Pos.x;
			m_Rect.m_Right	= m_Pos.x + tex->Width;
		}
	}

	~Button()
	{}

	void Update()override;

	void Draw()override;

private:

	void Init()override;
	void Release()override;
	

private:
	void (*m_PushedFunc)(void);
	std::string m_Normal;
	std::string m_Hover;
	Rect m_Rect;
	bool m_IsHover;
};

#endif