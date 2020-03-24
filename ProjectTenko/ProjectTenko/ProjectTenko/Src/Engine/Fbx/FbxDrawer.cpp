#include "FbxDrawer.h"
#include "fbxsdk.h"

void FbxDrawer::RenderFbxMesh(FBXMeshData* pData_)
{
	if (pData_ == nullptr) return;

	Skinning(pData_);

	RenderModel(&pData_->Model);
}

void FbxDrawer::Animate(FBXMeshData * pData_, float sec_)
{
	if (pData_ == nullptr) return;
	if (pData_->Model.pMotion == nullptr) return;
	//	モーション時間の更新
	pData_->frame += sec_ * 60.0f;

	//	ループチェック
	if (pData_->frame >= (*pData_->Model.pMotion)[pData_->motion].numFrame - 1)
	{
		// ループ
		pData_->frame = 0;
	}
}

void FbxDrawer::ResetAnimate(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;
	pData_->frame = 0;
}

void FbxDrawer::Skinning(FBXMeshData * pData_)
{
	if (!pData_->Model.pMotion) return;

	Motion* pMotion = &(*pData_->Model.pMotion)[pData_->motion];
	if (pMotion == nullptr) return;
	if (pMotion->numFrame < 0) return;

	float Frame = pData_->frame;
	//	配列用変数
	int f = (int)Frame;
	//	行列準備
	D3DXMATRIX KeyMatrix[256];
	for (UINT b = 0; b < pData_->Model.boneNum; b++)
	{
		if (!pMotion->pKey[b]) continue;
		//	行列補間
		D3DXMATRIX m;
		MatrixInterporate(m, pMotion->pKey[b][f], pMotion->pKey[b][f + 1], Frame - (int)Frame);
		pData_->Model.bone[b].transform = m;
		//	キーフレーム
		KeyMatrix[b] = pData_->Model.bone[b].offset * m;
	}

	//	頂点変形
	for (UINT meshIdx = 0; meshIdx < pData_->Model.meshNum; meshIdx++)
	{
		MeshData* pMeshData = &pData_->Model.pMesh[meshIdx];
		MeshVertex* pSrcVertices = pMeshData->pVertices;

		UINT size = (UINT)(pMeshData->vertexNum * sizeof(MeshVertex));
		MeshVertex* pVertices;
		// バッファをロックしてデータを書き込む
		pMeshData->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);
		for (UINT v = 0; v < pMeshData->vertexNum; v++)
		{
			//	頂点 * ボーン行列
			// b = v番目の頂点の影響ボーン[n]
			if (pVertices[v].weight[0] <= 0) continue;

			pVertices[v].x = 0;
			pVertices[v].y = 0;
			pVertices[v].z = 0;

			//	影響個数分ループ
			for (int n = 0; n < 4; n++)
			{
				if (pVertices[v].weight[n] <= 0) break;

				int b = (int)pVertices[v].index[n];

				float x = pSrcVertices[v].x;
				float y = pSrcVertices[v].y;
				float z = pSrcVertices[v].z;
				//	座標を影響力分移動
				pVertices[v].x += (x * KeyMatrix[b]._11 + y * KeyMatrix[b]._21 + z * KeyMatrix[b]._31 + 1 * KeyMatrix[b]._41) * pVertices[v].weight[n];
				pVertices[v].y += (x * KeyMatrix[b]._12 + y * KeyMatrix[b]._22 + z * KeyMatrix[b]._32 + 1 * KeyMatrix[b]._42) * pVertices[v].weight[n];
				pVertices[v].z += (x * KeyMatrix[b]._13 + y * KeyMatrix[b]._23 + z * KeyMatrix[b]._33 + 1 * KeyMatrix[b]._43) * pVertices[v].weight[n];

				float nx = pSrcVertices[v].nx;
				float ny = pSrcVertices[v].ny;
				float nz = pSrcVertices[v].nz;
				//	法線を影響力分変換
				pVertices[v].nx += (nx * KeyMatrix[b]._11 + ny * KeyMatrix[b]._21 + nz * KeyMatrix[b]._31) * pVertices[v].weight[n];
				pVertices[v].ny += (nx * KeyMatrix[b]._12 + ny * KeyMatrix[b]._22 + nz * KeyMatrix[b]._32) * pVertices[v].weight[n];
				pVertices[v].nz += (nx * KeyMatrix[b]._13 + ny * KeyMatrix[b]._23 + nz * KeyMatrix[b]._33) * pVertices[v].weight[n];
			}
		}
		pMeshData->pVertexBuffer->Unlock();
	}
}

void FbxDrawer::MatrixInterporate(D3DXMATRIX & out_, D3DXMATRIX & A_, D3DXMATRIX B_, float rate_)
{
	out_ = A_ * (1.0f - rate_) + B_ * rate_;
}
