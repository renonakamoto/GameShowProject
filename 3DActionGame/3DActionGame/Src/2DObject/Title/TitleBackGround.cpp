#include "TitleBackGround.h"
#include "../../Engine/Texture/Texture.h"

void TitleBackground::Update()
{
}

void TitleBackground::Draw()
{
	TextureManager::GetInstance()->Render(m_TexKeyword, m_Pos);
}

void TitleBackground::Init()
{
}

void TitleBackground::Release()
{
}
