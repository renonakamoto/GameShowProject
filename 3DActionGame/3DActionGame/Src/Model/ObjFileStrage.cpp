#include "ObjFileStrage.h"
#include "../Engine/DirectGraphics.h"

bool ObjFileStrage::LoadModel(const char* fileName_, std::string keyword_)
{
	
	
	return m_ModelData[keyword_].Load(fileName_, DirectGraphics::GetInstance()->GetDevice(), DirectGraphics::GetInstance()->GetSimpleVertexShader());;
}

void ObjFileStrage::Release(std::string keyword_)
{
}

void ObjFileStrage::AllRelease()
{
}
