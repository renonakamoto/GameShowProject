#include "3DHelper.h"
#include "../Engine/Graphics/DirectGraphics.h"
#include "../Engine/Texture/Texture.h"
#include <string>

typedef MySingletonTemplate::SingletonTemplate<MyDirectGraphics::DirectGraphics> DirectGraphics;
#define THE_GRAPHICS DirectGraphics::GetInstance()

// マテリアル情報の初期化
void InitMaterial(MaterialData* pMaterial, int materialNum)
{
	ZeroMemory(pMaterial, sizeof(MaterialData) * materialNum);

	D3DMATERIAL9 material;
	//	材質設定
	//	アンビエント(環境)カラー
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	//	ディフューズ(素材の)カラー
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 1.0f;
	material.Diffuse.b = 1.0f;
	material.Diffuse.a = 1.0f;
	//	スペキュラー（テカり）カラー
	material.Specular.r = 1.0f;
	material.Specular.g = 1.0f;
	material.Specular.b = 1.0f;
	material.Specular.a = 1.0f;
	material.Power = 15.0f;
	//	エミッシブ（発光）
	material.Emissive.r = 0.0f;
	material.Emissive.g = 0.0f;
	material.Emissive.b = 0.0f;
	material.Emissive.a = 0.0f;

	for (int i = 0; i < materialNum; i++)
	{
		pMaterial[i].material = material;
	}
}

void RenderModel(Model* pModel)
{
	if (pModel == NULL) return;
	if (pModel->materialNum == 0) return;

	IDirect3DDevice9 * pDevice = THE_GRAPHICS->GetD3DDevice();
	pDevice->SetTransform(D3DTS_WORLD, &pModel->world);

	for (UINT matIdx = 0; matIdx < pModel->materialNum; matIdx++)
	{
		MaterialData* pMaterial = &pModel->pMaterial[matIdx];
		// テクスチャーの設定
		pDevice->SetTexture(0, pMaterial->textureData.pTexture);

		pDevice->SetMaterial(&pMaterial->material);
		for (UINT meshIdx = 0; meshIdx < pModel->meshNum; meshIdx++)
		{
			MeshData* pMesh = &pModel->pMesh[meshIdx];
			if (matIdx != pMesh->materialIndex)
			{
				continue;
			}

			// 頂点バッファの設定
			pDevice->SetStreamSource(0, pMesh->pVertexBuffer, 0, pMesh->vertexStride);

			// 頂点フォーマットの指定
			pDevice->SetFVF(pMesh->fvf);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			if (pMesh->pIndexBuffer)
			{
				// インデックスバッファの設定
				pDevice->SetIndices(pMesh->pIndexBuffer);
				// 描画
				pDevice->DrawIndexedPrimitive(pMesh->primType, 0, 0, pMesh->vertexNum, 0, pMesh->primNum);
			}
			else
			{
				// 描画
				pDevice->DrawPrimitive(pMesh->primType, 0, pMesh->primNum);
			}
		}
	}
}


void ReleaseModel(Model* pModel)
{
	if (pModel == NULL) return;

	for (UINT i = 0; i < pModel->meshNum; i++)
	{
		SAFE_RELEASE(pModel->pMesh[i].pVertexBuffer);
		SAFE_RELEASE(pModel->pMesh[i].pIndexBuffer);
		free(pModel->pMesh[i].pVertices);
	}
	for (UINT i = 0; i < pModel->materialNum; i++)
	{
		ReleaseTexture(&pModel->pMaterial[i].textureData);
	}
	if (pModel->pMotion)
	{
		std::map<std::string, Motion>::iterator it;
		for (it = pModel->pMotion->begin(); it != pModel->pMotion->end(); it++)
		{
			for (int i = 0; i < 256; i++)
			{
				if (it->second.pKey[i])
				{
					free(it->second.pKey[i]);
				}
			}
		}
		delete pModel->pMotion;
	}
	free(pModel->pMesh);
	free(pModel->pMaterial);

	ZeroMemory(pModel, sizeof(Model));
}

// 頂点バッファの生成
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = THE_GRAPHICS->GetD3DDevice();
	// 指定したサイズの頂点バッファを作成
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pVertices, size);
			pVertexBuffer->Unlock();
		}
	}
	return pVertexBuffer;
}

// インデックスバッファの生成
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = THE_GRAPHICS->GetD3DDevice();
	// 16byte型のインデックスバッファを作成
	if (FAILED(pDevice->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pIndexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pIndeces, size);
			pIndexBuffer->Unlock();
		}
	}
	return pIndexBuffer;
}