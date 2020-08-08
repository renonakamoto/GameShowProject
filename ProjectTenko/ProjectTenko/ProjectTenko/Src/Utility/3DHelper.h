#ifndef D3DHELPER_H_
#define D3DHELPER_H_

#include "../Engine/Texture/Texture.h"
#include <d3dx9.h>
#include <map>
#include <string>

#define FVF_SIMPLE_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define FVF_SIMPLE_TEX_3D   (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	FVF_MESH_VERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);
#define	FVF_MESH_TEX_VERTEX	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE);

struct MeshVertex
{
	float x, y, z;
	float nx, ny, nz;
	DWORD color;
	float u, v;

	// スキンメッシュ用
	BYTE index[4];
	float weight[4];
};

struct MaterialData
{
	TextureData		textureData;	// テクスチャ―
	D3DMATERIAL9	material;		// マテリアル
};

// ボーン情報
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};

// モデル情報
struct MeshData
{
	UINT					fvf;			// フォーマット
	D3DPRIMITIVETYPE		primType;		// プリミティブの描画方法
	UINT					primNum;		// プリミティブ数
	UINT					vertexNum;		// 頂点数
	UINT					vertexStride;	// 1頂点辺りのサイズ
	UINT					indexNum;		// インデックス数
	UINT					materialIndex;	// マテリアル番号

	MeshVertex*				pVertices;		// 頂点データ
	IDirect3DVertexBuffer9* pVertexBuffer;	// 頂点バッファ
	IDirect3DIndexBuffer9*	pIndexBuffer;	// インデックスバッファ
};

static const int BONE_MAX = 256;

//	アニメーション
struct Motion
{
	Motion()
	{
		ZeroMemory(pKey, sizeof(pKey));
	}

	UINT		numFrame;		// フレーム数	
	D3DXMATRIX* pKey[BONE_MAX];	// キーフレーム
};

// モデル情報
struct Model
{
	UINT							meshNum;		// メッシュ数
	UINT							materialNum;	// マテリアル数
	UINT							boneNum;		// ボーン数

	MeshData*						pMesh;			// メッシュ情報
	MaterialData*					pMaterial;		// マテリアル情報
	Bone							bone[BONE_MAX];	// ボーン情報
	int								startFrame;		// 開始フレーム
	std::map<std::string, Motion>*	pMotion;		// モーション

	D3DXMATRIX						world;			// ワールドマトリックス
};


// FBXメッシュ(DX9用)
// 今だけ
struct FBXMeshData
{
	Model	Model;		// メッシュデータ
	char	motion[64];	// モーション名
	float	frame;		// フレーム
};

// マテリアル情報の初期化
void InitMaterial(MaterialData* pMaterial, int materialNum);

// モデル描画
void RenderModel(Model* pModel);

// モデルの解放
void ReleaseModel(Model* pModel);

// 頂点バッファの生成
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size);
// インデックスバッファの生成
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size);


#endif