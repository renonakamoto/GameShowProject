#ifndef OBJFILE_STRAGE_H_
#define OBJFILE_STRAGE_H_

#include <map>
#include <string>
#include "../Engine/MeshModel/ObjModel/ObjModel.h"

class ObjFileStrage
{
public:
	// インスタンスを取得する関数
	static ObjFileStrage* GetInstance()
	{
		static ObjFileStrage instance;
		return &instance;
	}

	// 読み込み関数
	bool LoadModel(const char* fileName_, std::string keyword_);

	ObjModel* GetModel(std::string keyword_) { return &m_ModelData[keyword_]; }

	void Release(std::string keyword_);

	void AllRelease();

private:
	ObjFileStrage()
	{}

	~ObjFileStrage()
	{}

private:
	std::map<std::string, ObjModel> m_ModelData;

};

#endif