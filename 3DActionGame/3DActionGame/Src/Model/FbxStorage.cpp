#include "FbxStorage.h"

bool FbxStorage::LoadModel(const char* fileName_, std::string keyword_)
{
	// すでにキーが存在する場合は読み込みが終わっているので早期リターン
	//if (m_ModelData.find(keyword_.c_str()) != m_ModelData.end()) return true;
	
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
	// モデルが存在しないときは早期リターン
	//if (m_ModelData.find(modelKeyword_.c_str()) == m_ModelData.end()) return false;

	// 読み込み 
	return m_ModelData[modelKeyword_].LoadMotion(motionKeyword_, fileName_);
}

void FbxStorage::Release(std::string keyword_)
{
}

void FbxStorage::AllRelease()
{
}
