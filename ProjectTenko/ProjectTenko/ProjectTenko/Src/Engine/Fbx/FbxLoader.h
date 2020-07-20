#ifndef FBXLOADER_H_
#define FBXLOADER_H_

#include "../../Utility/3DHelper.h"
#include <fbxsdk.h>
#include <string>

/**
* @brief	Fbx�̓ǂݍ��݃N���X
* @details	FbxManager�ŊǗ������̂ŗ��p�҂������K�v�͂Ȃ�
*/
class FbxLoader
{
public:
	/**
	* @brief Fbx�̓ǂݍ���
	* @param[in] pFileName_ �t�@�C����(�p�X�t)
	* @return FBXMeshData ���b�V���f�[�^
	*/
	FBXMeshData LoadFBXMesh(const char* pFileName_);

	/**
	* @brief Fbx�̉��
	* @param[in] pData_ ���b�V���f�[�^
	*/
	void ReleaseFbxMesh(FBXMeshData* pData_);

private:
	char m_RootPath[MAX_PATH]; //! �t�@�C���̃p�X

	// FBX�̉�͗�
	// �}�e���A���̉��
	void LoadMaterial(MaterialData* pMaterialData_, FbxMesh* pMesh_);
	// �{�[���̉��
	void LoadBone(Model* pModel_, MeshData* pMeshData_, FbxMesh* pMesh_);
	int FindBone(Model* pModel_, const char* pName_);
	//	�L�[�t���[���ǂݍ���
	void LoadKeyFrames(Model* pModel_, std::string name_, int bone_, FbxNode* pBoneNode_);

	// ���b�V���̉�͗�
	bool LoadMesh(MeshData* pMeshData_, FbxMesh* pMesh_);
	// �C���f�N�X�o�b�t�@�̎擾
	void LoadIndeces(MeshData* pMeshData_, FbxMesh* pMesh_);
	// �o�[�e�b�N�o�b�t�@�̎擾
	void LoadPosition(MeshData* pMeshData_, FbxMesh* pMesh_);
	// UV�̉��
	void LoadUV(MeshData* pMeshData_, FbxMesh* pMesh_);
	// �F�̉��
	void LoadColor(MeshData* pMeshData_, FbxMesh* pMesh_);
	// �@���̉��
	void LoadNormal(MeshData* pMeshData_, FbxMesh* pMesh_);

	void Play(FBXMeshData* pData_, std::string name_);

};

#endif