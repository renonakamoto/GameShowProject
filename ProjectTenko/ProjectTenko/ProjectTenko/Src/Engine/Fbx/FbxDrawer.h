#ifndef FBXDRAWER_H_
#define FBXDRAWER_H_

#include "../../Utility/3DHelper.h"

/**
* @brief	Fbx�̕`��N���X
* @details	FbxManager�ŊǗ������̂ŗ��p�҂������K�v�͂Ȃ�
*/
class FbxDrawer
{
public:
	/**
	* @brief	�R���X�g���N�^
	*/
	FbxDrawer() {}

	/**
	* @brief	�f�X�g���N�^
	*/
	~FbxDrawer() {}

	/**
	* @brief	Fbx�̕`��
	*/
	void RenderFbxMesh(FBXMeshData* pData_, UCHAR alpha_ = 255);

	// FBX�̃A�j���[�V����
	// �`��ł͂Ȃ������̊֐����Ă΂Ȃ��ƃA�j���[�V�����ł��Ȃ�

	/**
	* @brief	Fbx�̃A�j���[�V�����֐�
	* @details	FbxManager�ŊǗ������̂ŗ��p�҂������K�v�͂Ȃ�
	*/
	void Animate(FBXMeshData* pData_, float sec_);

	/**
	* @brief	Fbx�̃A�j���[�V�����������֐�
	*/
	void ResetAnimate(FBXMeshData* pData_);

private:

	void Skinning(FBXMeshData* pData_);
	//	�{�[���s��̕��
	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

};

#endif