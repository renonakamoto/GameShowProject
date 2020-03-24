#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <d3dx9.h>

// �e�N�X�`���[�f�[�^
struct TextureData
{
	UINT				width;		// �e�N�X�`���[�̕�
	UINT				height;		// �e�N�X�`���[�̍���
	UINT				srcWidth;	// �摜�̕�
	UINT				srcHeight;	// �摜�̍���
	IDirect3DTexture9* pTexture;	// ���������e�N�X�`���[�̃|�C���^
};

// �e�N�X�`���[�̓ǂݍ���
bool LoadTexture(const char* pFileName, TextureData* pOut);

// �e�N�X�`���[�̉��
void ReleaseTexture(TextureData* pTextureData);

#endif