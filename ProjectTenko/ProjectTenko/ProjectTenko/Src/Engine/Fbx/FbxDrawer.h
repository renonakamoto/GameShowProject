#ifndef FBXDRAWER_H_
#define FBXDRAWER_H_

#include "../../Utility/3DHelper.h"

// FBX�̕`��֐�
// ���p�҂��G��K�v�͂Ȃ�
class FbxDrawer
{
public:
	// �R���X�g���N�^
	FbxDrawer() {}
	// �f�X�g���N�^
	~FbxDrawer() {}

	// FBX���b�V���̕`��
	void RenderFbxMesh(FBXMeshData* pData_, UCHAR alpha_ = 255);

	// FBX�̃A�j���[�V����
	// �`��ł͂Ȃ������̊֐����Ă΂Ȃ��ƃA�j���[�V�����ł��Ȃ�
	void Animate(FBXMeshData* pData_, float sec_);

	// �A�j���[�V����(�L�[�t���[��)�����Z�b�g����
	void ResetAnimate(FBXMeshData* pData_);

private:
	// �����炭���[�V�����ɂ�����鏈��
	void Skinning(FBXMeshData* pData_);
	//	�{�[���s��̕��
	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

};

#endif