#include "BackGround.h"
#include "../../Engine/Engine.h"

void Background::Draw()
{
	GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_BACK);
	TEX_MANAGER->Render(m_TexKeyword, m_Pos);
}