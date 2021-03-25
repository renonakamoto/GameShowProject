#include "FbxStorage.h"

bool FbxStorage::LoadModel(const char* fileName_, std::string keyword_)
{
	// すでにキーが存在する場合は読み込みが終わっているので早期リターン
	//for (auto itr = m_ModelData.begin(); itr != m_ModelData.end(); ++itr)
	//{
	//	if (itr->first == keyword_) return true;
	//}
	
	// 読み込み 
	if (m_ModelData[keyword_].LoadModel(fileName_) == true)
	{
		return true;
	}
	else
	{
		m_ModelData.erase(keyword_);
		return false;
	}
}

bool FbxStorage::LoadMotion(const char* fileName_, std::string modelKeyword_, std::string motionKeyword_)
{
	// 読み込み 
	return m_ModelData[modelKeyword_].LoadMotion(motionKeyword_, fileName_);
}

void FbxStorage::Release(std::string keyword_)
{
}

void FbxStorage::AllRelease()
{
}
