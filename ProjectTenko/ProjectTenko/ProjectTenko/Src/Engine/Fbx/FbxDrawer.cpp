#include "FbxDrawer.h"
#include "fbxsdk.h"
#include "../Graphics/DirectGraphics.h"

void FbxDrawer::RenderFbxMesh(FBXMeshData* pData_, UCHAR alpha_)
{
	if (pData_ == nullptr) return;

	Skinning(pData_);

	RenderModel(&pData_->Model);
}

void FbxDrawer::Animate(FBXMeshData * pData_, float sec_)
{
	if (pData_ == nullptr) return;
	if (pData_->Model.pMotion == nullptr) return;
	//	���[�V�������Ԃ̍X�V
	pData_->frame = sec_;

	//	���[�v�`�F�b�N
	if (pData_->frame >= (*pData_->Model.pMotion)[pData_->motion].numFrame - 1)
	{
		// ���[�v
		pData_->frame = 0.0f;
	}
}

void FbxDrawer::ResetAnimate(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;
	pData_->frame = 0;
}

void FbxDrawer::Skinning(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;
	if (!pData_->Model.pMotion) return;

	Motion* pMotion = &(*pData_->Model.pMotion)[pData_->motion];
	if (pMotion == nullptr) return;
	if (pMotion->numFrame < 0) return;

	float frame = pData_->frame;
	//	�z��p�ϐ�
	int f = static_cast<int>(frame);
	//	�s�񏀔�
	D3DXMATRIX key_matrix[256];
	for (UINT b = 0; b < pData_->Model.boneNum; b++)
	{
		if (!pMotion->pKey[b]) continue;
		//	�s����
		D3DXMATRIX m;
		MatrixInterporate(m, pMotion->pKey[b][f], pMotion->pKey[b][f + 1], frame - (int)frame);
		pData_->Model.bone[b].transform = m;
		//	�L�[�t���[��
		key_matrix[b] = pData_->Model.bone[b].offset * m;
	}

	//	���_�ό`
	for (UINT mesh_idx = 0; mesh_idx < pData_->Model.meshNum; mesh_idx++)
	{
		MeshData*   pMeshData    = &pData_->Model.pMesh[mesh_idx];
		MeshVertex* pSrcVertices = pMeshData->pVertices;

		UINT size = (UINT)(pMeshData->vertexNum * sizeof(MeshVertex));
		MeshVertex* pVertices;
		// �o�b�t�@�����b�N���ăf�[�^����������
		pMeshData->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);
		for (UINT v = 0; v < pMeshData->vertexNum; v++)
		{
			//	���_ * �{�[���s��
			// b = v�Ԗڂ̒��_�̉e���{�[��[n]
			if (pVertices[v].weight[0] <= 0) continue;

			pVertices[v].x = 0;
			pVertices[v].y = 0;
			pVertices[v].z = 0;

			//	�e���������[�v
			for (int n = 0; n < 4; n++)
			{
				if (pVertices[v].weight[n] <= 0) break;

				int b = (int)pVertices[v].index[n];

				float x = pSrcVertices[v].x;
				float y = pSrcVertices[v].y;
				float z = pSrcVertices[v].z;
				//	���W���e���͕��ړ�
				pVertices[v].x += (x * key_matrix[b]._11 + y * key_matrix[b]._21 + z * key_matrix[b]._31 + 1 * key_matrix[b]._41) * pVertices[v].weight[n];
				pVertices[v].y += (x * key_matrix[b]._12 + y * key_matrix[b]._22 + z * key_matrix[b]._32 + 1 * key_matrix[b]._42) * pVertices[v].weight[n];
				pVertices[v].z += (x * key_matrix[b]._13 + y * key_matrix[b]._23 + z * key_matrix[b]._33 + 1 * key_matrix[b]._43) * pVertices[v].weight[n];

				float nx = pSrcVertices[v].nx;
				float ny = pSrcVertices[v].ny;
				float nz = pSrcVertices[v].nz;
				//	�@�����e���͕��ϊ�
				pVertices[v].nx += (nx * key_matrix[b]._11 + ny * key_matrix[b]._21 + nz * key_matrix[b]._31) * pVertices[v].weight[n];
				pVertices[v].ny += (nx * key_matrix[b]._12 + ny * key_matrix[b]._22 + nz * key_matrix[b]._32) * pVertices[v].weight[n];
				pVertices[v].nz += (nx * key_matrix[b]._13 + ny * key_matrix[b]._23 + nz * key_matrix[b]._33) * pVertices[v].weight[n];
			}
		}
		pMeshData->pVertexBuffer->Unlock();
	}
}

void FbxDrawer::MatrixInterporate(D3DXMATRIX & out_, D3DXMATRIX & A_, D3DXMATRIX B_, float rate_)
{
	out_ = A_ * (1.0f - rate_) + B_ * rate_;
}