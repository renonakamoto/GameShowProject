#include "BackGround.h"
#include "../../Engine/Texture/Texture.h"

void Background::Draw()
{
	TextureManager::GetInstance()->Render(m_TexKeyword, m_Pos);
}