#ifndef OBJFILE_STRAGE_H_
#define OBJFILE_STRAGE_H_

#include <map>
#include <string>
#include "../Engine/Model/ObjModel/ObjModel.h"

/**
* @brief ObjFileのデータを保管するクラス
*/
class ObjFileStrage
{
public:
	/**
	* @fn static CollisionManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return CollisionManager* インスタンスのポインタ
	*/
	static ObjFileStrage* GetInstance()
	{
		static ObjFileStrage instance;
		return &instance;
	}

	// 読み込み関数
	bool LoadModel(const char* fileName_, std::string keyword_);

	/**
	* @fn ObjModel* GetModel(std::string keyword_)
	* @brief モデルのデータを返す関数
	* @param[in] keyword_ モデルに紐づけているキーワード
	* @return FbxModel* モデルデータのアドレス
	*/
	ObjModel* GetModel(std::string keyword_) { return &m_ModelData[keyword_]; }

	/**
	* @fn void Release(std::string keyword_)
	* @brief 特定のモデルデータを削除する関数
	* @param[in] keyword_ モデルに紐づけるキーワード
	*/
	void Release(std::string keyword_);

	/**
	* @fn void AllRelease()
	* @brief すべてのモデルデータを削除する関数
	*/
	void AllRelease();

private:
	/**
	* @brief コンストラクタ
	*/
	ObjFileStrage()
	{}

	/**
	* @brief デストラクタ
	*/
	~ObjFileStrage()
	{}

private:
	std::map<std::string, ObjModel> m_ModelData; //! モデルデータを保存する変数

};

#endif