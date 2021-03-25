#ifndef FBX_STORAGE_H_
#define FBX_STORAGE_H_

#include <map>
#include <string>
#include "../Engine/MeshModel/FbxModel/FbxModel.h"

/**
* @brief Fbxのデータを保管するクラス
*/
class FbxStorage
{
public:
	// インスタンスを取得する関数
	static FbxStorage* GetInstance()
	{
		static FbxStorage instance;
		return &instance;
	}

	// 読み込み関数
	bool LoadModel(const char* fileName_, std::string keyword_);
	bool LoadMotion(const char* fileName_, std::string modelKeyword_, std::string motionKeyword_);

	// 
	FbxModel* GetModel(std::string keyword_) { return &m_ModelData[keyword_]; }

	void Release(std::string keyword_);
	void AllRelease();
	
private:
	// コンストラクタ
	FbxStorage() {
		m_ModelData.clear();
	}
	// デストラクタ
	~FbxStorage() {}

private:
	std::map<std::string, FbxModel> m_ModelData;

};

#endif