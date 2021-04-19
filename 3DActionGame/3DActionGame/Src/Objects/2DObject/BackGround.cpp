#include "BackGround.h"
#include "../../Engine/Engine.h"

void Background::Draw()
{
	TEX_MANAGER->Render(m_TexKeyword, m_Pos);
}