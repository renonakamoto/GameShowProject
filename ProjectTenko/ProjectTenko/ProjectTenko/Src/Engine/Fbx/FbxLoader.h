#ifndef FBXLOADER_H_
#define FBXLOADER_H_

#include "../../Utility/3DHelper.h"
#include <fbxsdk.h>
#include <string>

/**
* @brief	Fbxの読み込みクラス
* @details	FbxManagerで管理されるので利用者がさわる必要はない
*/
class FbxLoader
{
public:
	/**
	* @brief Fbxの読み込み
	* @param[in] pFileName_ ファイル名(パス付)
	* @return FBXMeshData メッシュデータ
	*/
	FBXMeshData LoadFBXMesh(const char* pFileName_);

	/**
	* @brief Fbxの解放
	* @param[in] pData_ メッシュデータ
	*/
	void ReleaseFbxMesh(FBXMeshData* pData_);

private:
	char m_RootPath[MAX_PATH]; //! ファイルのパス

	// FBXの解析類
	// マテリアルの解析
	void LoadMaterial(MaterialData* pMaterialData_, FbxMesh* pMesh_);
	// ボーンの解析
	void LoadBone(Model* pModel_, MeshData* pMeshData_, FbxMesh* pMesh_);
	int FindBone(Model* pModel_, const char* pName_);
	//	キーフレーム読み込み
	void LoadKeyFrames(Model* pModel_, std::string name_, int bone_, FbxNode* pBoneNode_);

	// メッシュの解析類
	bool LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_);
	// インデクスバッファの取得
	void LoadIndeces(MeshData* pMeshData_, FbxMesh* pMesh_);
	// バーテックバッファの取得
	void LoadPosition(MeshData* pMeshData_, FbxMesh* pMesh_);
	// UVの解析
	void LoadUV(MeshData* pMeshData_, FbxMesh* pMesh_);
	// 色の解析
	void LoadColor(MeshData* pMeshData_, FbxMesh* pMesh_);
	// 法線の解析
	void LoadNormal(MeshData* pMeshData_, FbxMesh* pMesh_);

	void Play(FBXMeshData* pData_, std::string name_);

};

#endif