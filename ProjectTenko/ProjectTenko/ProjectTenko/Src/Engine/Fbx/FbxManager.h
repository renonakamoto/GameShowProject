#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

#include "FbxLoader.h"
#include "FbxDrawer.h"
#include <string>
#include <map>

namespace MyFbx
{
	/**
	* @brief Fbxを扱うクラス
	* @details Fbxの読み込みと描画を扱う
	*/
	class FbxManager
	{
	public:
		/**
		* @brief 簡単な説明（～する関数）
		* @param[in] key_ オブジェクトに設定するキー
		* @param[in] pFileName_ 読み込みたいFBXのファイル名(パス付)
		* @return bool 成功:true 失敗:false
		*/
		bool LoadFBXMesh(std::string key_, const char* pFileName_);

		/**
		* @brief 簡単な説明（～する関数）
		* @param[in] key_ オブジェクトに設定されているキー
		* @details キーで指定したオブジェクトの解放
		*/
		void ReleaseFbxMesh(std::string key_);

		/**
		* @brief 生成したオブジェクトをすべて解放する
		*/
		void AllReleaseFbxMesh();

		/**
		* @brief 描画する関数
		* @param[in] key_ オブジェクトに設定しているキー
		*/
		void Draw(std::string key_);

		/**
		* @brief アニメーション関数
		* @param[in] key_ オブジェクトに設定されているキー
		* @param[in] sec_ 
		* @details Fbxメッシュの
		*/
		void Animation(std::string key_, float sec_);

		/**
		* @brief 簡単な説明（～する関数）
		* @param[in] key_ オブジェクトに設定されているキー
		* @details Fbxメッシュの
		*/
		void ResetAnimation(std::string key_);

	private:

		/**
		* @brief m_ObjectMeshDataが引数のキーを持っているか調べる関数
		* @param[in] key_ オブジェクトに設定されているキー
		* @return bool 持っている:true 持っていない:false
		*/
		bool HasKey(std::string key_);

		//! オブジェクトを保存する変数
		std::map<std::string, FBXMeshData> m_ObjectMeshData;

		//! 読み込み担当クラス
		FbxLoader* m_FbxLoader;
		//! 描画担当クラス
		FbxDrawer* m_FbxDrawe;
	};
}


#endif