#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

#include "../../Utility/SingletonTemplate.h"
#include "FbxLoader.h"
#include "FbxDrawer.h"
#include <string>
#include <map>
#include <memory>

namespace MyFbx
{
	/**
	* @brief	Fbxを扱うクラス
	* @details	Fbxの読み込みと描画を扱う
	*/
	class FbxManager
	{

		friend MySingletonTemplate::SingletonTemplate<FbxManager>;
	public:
		/**
		* @brief Fbxの読み込み
		* @param[in] key_ FbxDataに設定するキー
		* @param[in] pFileName_ 読み込みたいFBXのファイル名(パス付)
		* @return bool 成功:true 失敗:false
		*/
		bool LoadFBXMesh(std::string key_, const char* pFileName_);

		/**
		* @brief 指定したMeshDataを削除
		* @param[in] key_ FbxData設定されているキー
		* @details キーで指定したオブジェクトの解放
		*/
		void ReleaseFbxMesh(std::string key_);

		/**
		* @brief すべてのMeshDataを削除
		*/
		void AllReleaseFbxMesh();

		/**
		* @brief Fbxの描画関数
		* @param[in] key_	FbxData設定されているキー
		* @param[in] world_ 読み込みたいFBXのファイル名(パス付)
		*/
		void Draw(std::string key_, const D3DXMATRIX& world_, UCHAR alpha_ = 255);

		/**
		* @brief アニメーション関数
		* @param[in] key_	FbxData設定されているキー
		* @param[in] sec_	キーフレーム
		* @details 描画関数ではないのでUpdate中に使用してください
		*/
		void Animation(std::string key_, float sec_);

		/**
		* @brief アニメーションの初期化
		* @param[in] key_ FbxData設定されているキー
		*/
		void ResetAnimation(std::string key_);

	private:
		/**
		* @brief コンストラクタ
		*/
		FbxManager();

		/**
		* @brief デストラクタ
		*/
		~FbxManager();

		/**
		* @brief m_ObjectMeshDataが引数のキーを持っているか調べる関数
		* @param[in] key_ オブジェクトに設定されているキー
		* @return bool 持っている:true 持っていない:false
		*/
		bool HasKey(std::string key_);

		//! オブジェクトを保存する変数
		std::map<std::string, FBXMeshData*> m_ObjectMeshData;

		//! 読み込み担当クラス
		std::unique_ptr<FbxLoader> m_FbxLoader;
		//! 描画担当クラス
		std::unique_ptr<FbxDrawer> m_FbxDrawe;
	};
}

typedef MySingletonTemplate::SingletonTemplate<MyFbx::FbxManager> FbxMeshManager;
#define THE_FBXMANAGER FbxMeshManager::GetInstance()

#endif