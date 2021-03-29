#ifndef TITLE_BACKGROUND_H_
#define TITLE_BACKGROUND_H_

#include "../../ObjectManager/Object2D.h"
#include <string>

class TitleBackground : public Object2D
{
public:
	TitleBackground(std::string keyword_):
		m_TexKeyword(keyword_)
	{
		Init();
	}

	TitleBackground(std::string keyword_, DirectX::XMFLOAT3 pos_) :
		Object2D(pos_),
		m_TexKeyword(keyword_)
	{
		Init();
	}

	~TitleBackground()
	{
		Release();
	}
	
	void Update()override;
	void Draw()override;
	
private:
	void Init()override;
	void Release()override;

private:
	std::string m_TexKeyword;

};

#endif