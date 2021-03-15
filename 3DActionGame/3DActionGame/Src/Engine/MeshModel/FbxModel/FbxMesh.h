#ifndef FBX_LOADER_H_
#define FBX_LOADER_H

#include <d3dx11.h>
#include <Windows.h>
#include <map>
#include <vector>
#include <fbxsdk.h>
#include "../../../Utility/GraphicsUtility.h"
#include "../../VertexShader.h"
#include "../../DirectGraphics.h"

static const int MOTION_MAX = 256;
static const int BONE_MAX = 255;


/**
* @brief ボーン情報を保持する構造体
*/
struct Bone
{
	char			  Name[64];		//! ボーン名
	DirectX::XMMATRIX Offset;		//! 初期姿勢行列
	DirectX::XMMATRIX Transform;	
};

/**
* @brief モーション情報を保持するクラス
*/
struct Motion
{
	UINT FrameNum;								  //! フレーム数
	std::vector<DirectX::XMMATRIX> Key[BONE_MAX]; //! フレーム時姿勢行列
};

/**
* @brief モーション情報を保持するクラス
*/
class FbxModel
{
public:
	struct MeshData
	{
		MeshData() :
			m_VertexBuffer(nullptr),
			m_IndexBuffer(nullptr)
		{}

		ID3D11Buffer* m_VertexBuffer;
		ID3D11Buffer* m_IndexBuffer;
		std::vector<CVertex> m_Vertices;
		std::vector<UINT>	 m_Indices;
		std::string			 m_MaterialName;
	};

public:
	FbxModel() :
		m_InputLayout(nullptr)
	{
		m_MeshList.clear();
		m_Materials.clear();
	}

	~FbxModel()
	{
		for (auto mesh : m_MeshList)
		{
			if (mesh.m_VertexBuffer != nullptr)
			{
				mesh.m_VertexBuffer->Release();
			}

			if (mesh.m_IndexBuffer != nullptr)
			{
				mesh.m_IndexBuffer->Release();
			}
			mesh.m_Indices.clear();
			mesh.m_Vertices.clear();
		}

		if (m_InputLayout != nullptr)
		{
			m_InputLayout->Release();
			m_InputLayout = nullptr;
		}
	}

	bool Load(const char* fileName_, ID3D11Device* device_, VertexShader* vertexShader_);
	bool LoadMotion(std::string keyword_, const char* fileName_);

	void Render(DirectGraphics* graphics_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_);
	void Play(std::string animName_);
	void Animate(float sec_ = 1.0f / 60.0f);

	bool AddMesh(const char* fileName_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, const char* boneName_);

	

private:
	/**
	* @fn void LoadMaterial(ID3D11Device* device_, int b)
	* @brief マテリアルを読み込む関数
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @details 詳細な説明
	*/
	void LoadMaterial(FbxSurfaceMaterial* material_);

	/**
	* @fn void function(int a, int b)
	* @brief 簡単な説明（～する関数）
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @return bool 戻り値の説明
	* @details 詳細な説明
	*/
	void LoadIndices(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void function(int a, int b)
	* @brief 簡単な説明（～する関数）
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @return bool 戻り値の説明
	* @details 詳細な説明
	*/
	void LoadVertices(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void function(int a, int b)
	* @brief 簡単な説明（～する関数）
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @return bool 戻り値の説明
	* @details 詳細な説明
	*/
	void LoadNormals(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void function(int a, int b)
	* @brief 簡単な説明（～する関数）
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @return bool 戻り値の説明
	* @details 詳細な説明
	*/
	void LoadVertexColors(MeshData& meshData_, FbxMesh* mesh_);

	/**
	* @fn void function(int a, int b)
	* @brief 簡単な説明（～する関数）
	* @param[in] a(引数名) 引数の説明
	* @param[out] b(引数名) 引数の説明
	* @return bool 戻り値の説明
	* @details 詳細な説明
	*/
	void LoadMaterialNames(MeshData& meshData_, FbxMesh* mesh_);
	void LoadUV(MeshData& meshData_, FbxMesh* mesh_);
	void LoadBones(MeshData& meshData_, FbxMesh* mesh_);
	void LoadKeyFrame(std::string keyword_, int bone, FbxNode* boneNode_);
	bool LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_);
	int FindBoone(const char* boneName_);

	bool CreateVertexBuffer(ID3D11Device* device_);
	bool CreateIndexBuffer(ID3D11Device* device_);
	bool CreateInputLayout(ID3D11Device* device_, VertexShader* vertexShader_);

private:
	std::vector<MeshData>							 m_MeshList;		//! メッシュリスト
	std::map<std::string, ObjMaterial>				 m_Materials;		//! マテリアル
	std::map<std::string, ID3D11ShaderResourceView*> m_MaterialLinks;

	std::map<std::string, ID3D11ShaderResourceView*> m_Textures;		//! テクスチャ
	std::map<std::string, Motion>					 m_Motion;			//! モーションを
	Bone m_Bone[BONE_MAX];
	UINT m_BoneNum;														//! ボーンの数
	std::string m_PlayMotion;											//! 再生されているモーション名
	int   m_StartFrame;	//! モーションの開始フレームを保存する変数
	float m_Frame;		//! 現在のモーションのフレーム数を保持する変数


	ID3D11InputLayout* m_InputLayout;									//! 入力レイアウト
};

#endif
