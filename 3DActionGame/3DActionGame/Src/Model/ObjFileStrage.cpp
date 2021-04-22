#include "ObjFileStrage.h"

bool ObjFileStrage::LoadModel(const char* fileName_, std::string keyword_)
{
	// すでにキーが存在する場合は読み込みが終わっているので早期リターン
	if (m_ModelData.find(keyword_) != m_ModelData.end()) return true;
	
	// 読み込み
	if (m_ModelData[keyword_].Load(fileName_) == true)
	{
		return true;
	}
	else
	{
		m_ModelData.erase(keyword_);
		return false;
	}
}

void ObjFileStrage::Release(std::string keyword_)
{
	std::map<std::string, ObjModel>::iterator itr = m_ModelData.find(keyword_);
	if (itr != m_ModelData.end())
	{
		m_ModelData.erase(itr);
	}
}

void ObjFileStrage::AllRelease()
{
	if (m_ModelData.empty()) return;
	m_ModelData.clear();
}
