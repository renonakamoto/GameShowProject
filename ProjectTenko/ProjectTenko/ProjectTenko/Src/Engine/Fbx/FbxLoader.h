#ifndef FBXLOADER_H_
#define FBXLOADER_H_

#include "../../Utility/3DHelper.h"
#include <fbxsdk.h>
#include <string>

// FBXの読み込みと解放クラス
// 利用者が触る必要はない
class FbxLoader
{
public:
	// FBXメッシュの読み込み
	FBXMeshData LoadFBXMesh(const char* pFileName_);
	// FBXメッシュの解放
	void ReleaseFbxMesh(FBXMeshData* pData_);
	// モーションの読み込み(仮)
	void LoadMotion(Model* pModel_, std::string name_, const char* pFilename_);

private:
	char m_RootPath[MAX_PATH]; // ファイルのパス

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

	// おそらくモーションに名前を付けてる
	void Play(FBXMeshData* pData_, std::string name_);

};

#endif