#ifndef TITLE_BACKGROUND_H_
#define TITLE_BACKGROUND_H_

#include "../../ObjectManager/Object2D.h"


class TitleBackground : public Object2D
{
public:
	TitleBackground()
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

	
};

#endif