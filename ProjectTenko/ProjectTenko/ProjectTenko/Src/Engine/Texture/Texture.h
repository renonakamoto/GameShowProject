#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <map>
#include <string>

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

namespace MyTextureManager
{
	class TextureManager
	{

		friend MySingletonTemplate::SingletonTemplate<TextureManager>;
	public:

		bool Load(std::string key_);

		TextureData* GetTexturue(std::string key_);

		void Release(std::string key_);

		void AllRelease();

		void DrawTexture(float posX_, float posY_, std::string key_);

		void DrawTexture(float posX_, float posY_, float tu_, float tv_, std::string key_);

	private:
		TextureManager() {
		}

		~TextureManager();

		std::map<std::string, TextureData*> m_TextureMap;

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyTextureManager::TextureManager> TextureManager;
#define THE_TEXTUREMANAGER TextureManager::GetInstance()

#endif