#ifndef FONT_H_
#define FONT_H_

#include "../../Utility/SingletonTemplate.h"
#include <string>
#include <d3dx9.h>

namespace MyFontDevice
{
	enum class FontColor : unsigned char
	{
		Black,		//! 黒
		White,		//! 白
		Red,		//! 赤
		Yellow,		//! 黄
	};

	enum class FontSize : int
	{
		Small,		//! 小
		Regular,	//! 中
		Large,		//! 大

		FontSizeMax,//! サイズ最大数
	};

	class Font
	{
		
		friend MySingletonTemplate::SingletonTemplate<Font>;
	public:
		bool Init();

		void DrawFont(float posX_, float posY_, std::string text_, FontSize fontSize_ = FontSize::Regular, FontColor fontColor_ = FontColor::Black);

	private:
		

		Font(){}
		~Font() {}

		const int SmallFontSize   = 16;
		const int RegularFontSize = 24;
		const int LargeFontSize   = 64;

		LPD3DXFONT m_FontList[static_cast<int>(FontSize::FontSizeMax)];

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyFontDevice::Font> FontDevice;
#define THE_FONT FontDevice::GetInstance()

#endif