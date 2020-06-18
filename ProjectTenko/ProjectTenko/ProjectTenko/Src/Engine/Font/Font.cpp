#include "Font.h"
#include "../Graphics/DirectGraphics.h"
#include <string>

bool MyFontDevice::Font::Init()
{
	int font_size_max = static_cast<int> (FontSize::FontSizeMax);

	int size_list[] = {
		SmallFontSize,
		RegularFontSize,
		LargeFontSize
	};

	for (int i = 0; i < font_size_max; ++i)
	{
		if (FAILED(D3DXCreateFont(THE_GRAPHICS->GetD3DDevice(),
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("MS PÉSÉVÉbÉN"),
			&m_FontList[i])))
		{
			return false;
		}
	}

	return true;
}

void MyFontDevice::Font::DrawFont(float posX_, float posY_, std::string text_, FontSize fontSize_, FontColor fontColor_)
{
	RECT rect = {
		static_cast<long> (posX_),
		static_cast<long> (posY_),
		static_cast<long> (posX_ + 1500),
		static_cast<long> (posY_ + 200)
	};

	int r, g, b;
	r = g = b = 255;

	if (fontColor_ == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (fontColor_ == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}
	else if (fontColor_ == FontColor::Yellow)
	{
		r = 255;
		g = 215;
		b = 20;
	}

	int font_size = static_cast<int>(fontSize_);

	m_FontList[font_size]->DrawTextA(
		nullptr,
		text_.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}
