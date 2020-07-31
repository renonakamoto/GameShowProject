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

	// �X�L�����b�V���p
	BYTE index[4];
	float weight[4];
};

struct MaterialData
{
	TextureData		textureData;	// �e�N�X�`���\
	D3DMATERIAL9	material;		// �}�e���A��
};

// �{�[�����
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};

// ���f�����
struct MeshData
{
	UINT					fvf;			// �t�H�[�}�b�g
	D3DPRIMITIVETYPE		primType;		// �v���~�e�B�u�̕`����@
	UINT					primNum;		// �v���~�e�B�u��
	UINT					vertexNum;		// ���_��
	UINT					vertexStride;	// 1���_�ӂ�̃T�C�Y
	UINT					indexNum;		// �C���f�b�N�X��
	UINT					materialIndex;	// �}�e���A���ԍ�

	MeshVertex*				pVertices;		// ���_�f�[�^
	IDirect3DVertexBuffer9* pVertexBuffer;	// ���_�o�b�t�@
	IDirect3DIndexBuffer9*	pIndexBuffer;	// �C���f�b�N�X�o�b�t�@
};

static const int BONE_MAX = 256;

//	�A�j���[�V����
struct Motion
{
	Motion()
	{
		ZeroMemory(pKey, sizeof(pKey));
	}

	UINT		numFrame;		// �t���[����	
	D3DXMATRIX* pKey[BONE_MAX];	// �L�[�t���[��
};

// ���f�����
struct Model
{
	UINT							meshNum;		// ���b�V����
	UINT							materialNum;	// �}�e���A����
	UINT							boneNum;		// �{�[����

	MeshData*						pMesh;			// ���b�V�����
	MaterialData*					pMaterial;		// �}�e���A�����
	Bone							bone[BONE_MAX];	// �{�[�����
	int								startFrame;		// �J�n�t���[��
	std::map<std::string, Motion>*	pMotion;		// ���[�V����

	D3DXMATRIX						world;			// ���[���h�}�g���b�N�X
};


// FBX���b�V��(DX9�p)
// ������
struct FBXMeshData
{
	Model	Model;		// ���b�V���f�[�^
	char	motion[64];	// ���[�V������
	float	frame;		// �t���[��
};

// �}�e���A�����̏�����
void InitMaterial(MaterialData* pMaterial, int materialNum);

// ���f���`��
void RenderModel(Model* pModel);

// ���f���̉��
void ReleaseModel(Model* pModel);

// ���_�o�b�t�@�̐���
IDirect3DVertexBuffer9* CreateVertexBuffer(const void* pVertices, UINT size);
// �C���f�b�N�X�o�b�t�@�̐���
IDirect3DIndexBuffer9* CreateIndexBuffer(const UINT16* pIndeces, UINT size);


#endif