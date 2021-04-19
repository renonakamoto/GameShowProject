#ifndef FBX_STORAGE_H_
#define FBX_STORAGE_H_

#include <map>
#include <string>
#include "../Engine/Model/FbxModel/FbxModel.h"

/**
* @brief FbxFileのデータを保管するクラス
*/
class FbxStorage
{
public:
	/**
	* @fn static CollisionManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return CollisionManager* インスタンスのポインタ
	*/
	static FbxStorage* GetInstance()
	{
		static FbxStorage instance;
		return &instance;
	}

	/**
	* @fn bool LoadModel(const char* fileName_, std::string keyword_)
	* @brief Fbxの読み込みを行う関数
	* @param[in] fileName_ ファイル名(パス付き)
	* @param[in] keyword_ モデルに紐づけるキーワード
	* @return bool 成功したかを真偽で返す
	*/
	bool LoadModel(const char* fileName_, std::string keyword_);

	/**
	* @fn bool LoadMotion(const char* fileName_, std::string modelKeyword_, std::string motionKeyword_)
	* @brief モーションの読み込みを行う関数
	* @param[in] fileName_ ファイル名(パス付き)
	* @param[in] modelKeyword_ モデルのキーワード
	* @param[in] motionKeyword_ モーションに紐づけるキーワード
	* @return bool 成功したかを真偽で返す
	*/
	bool LoadMotion(const char* fileName_, std::string modelKeyword_, std::string motionKeyword_);

	/**
	* @fn FbxModel* GetModel(std::string keyword_)
	* @brief モデルのデータを返す関数
	* @param[in] keyword_ モデルに紐づけているキーワード
	* @return FbxModel* モデルデータのアドレス
	*/
	FbxModel* GetModel(std::string keyword_) { return &m_ModelData[keyword_]; }

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
	FbxStorage()
	{}
	
	/**
	* @brief デストラクタ
	*/
	~FbxStorage()
	{
		AllRelease();
	}

private:
	std::map<std::string, FbxModel> m_ModelData; //! モデルデータを保存する変数

};

#endif