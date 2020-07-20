#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <map>
#include <string>

/**
* @brief �e�N�X�`���f�[�^�\����
*/
struct TextureData
{
	UINT				width;		//! �e�N�X�`���[�̕�
	UINT				height;		//! �e�N�X�`���[�̍���
	UINT				srcWidth;	//! �摜�̕�
	UINT				srcHeight;	//! �摜�̍���
	IDirect3DTexture9* pTexture;	//! ���������e�N�X�`���[�̃|�C���^
};

// �e�N�X�`���[�̓ǂݍ���
bool LoadTexture(const char* pFileName, TextureData* pOut);

// �e�N�X�`���[�̉��
void ReleaseTexture(TextureData* pTextureData);

namespace MyTextureManager
{
	/**
	* @brief �e�N�X�`���[�}�l�[�W���[�N���X
	*/
	class TextureManager
	{

		friend MySingletonTemplate::SingletonTemplate<TextureManager>;
	public:
		/**
		* @brief �e�N�X�`���[�̓ǂݍ��݊֐�
		* @param[in] key_  �e�N�X�`���ɐݒ肷��L�[
		* @return bool ture: ���� false: ���s
		*/
		bool Load(std::string key_);

		/**
		* @brief �e�N�X�`���f�[�^�擾�֐�
		* @param[in] key_  �e�N�X�`���L�[
		* @return TextureData* 
		*/
		TextureData* GetTexture(std::string key_);

		/**
		* @brief �e�N�X�`���`��֐�
		* @param[in] posX_  X���W
		* @param[in] posY_  Y���W
		* @param[in] key_   �e�N�X�`���ɐݒ肳��Ă���L�[
		*/
		void DrawTexture(float posX_, float posY_, std::string key_);

		/**
		* @brief �e�N�X�`���`��֐�
		* @param[in] posX_  X���W
		* @param[in] posY_  Y���W
		* @param[in] tu_	tu�l
		* @param[in] tv_	tv�l
		* @param[in] key_   �e�N�X�`���ɐݒ肳��Ă���L�[
		*/
		void DrawTexture(float posX_, float posY_, float tu_, float tv_, std::string key_);

		/**
		* @brief �e�N�X�`������֐�
		* @param[in] key_	�e�N�X�`���ɐݒ肳��Ă���L�[
		*/
		void Release(std::string key_);

		/**
		* @brief �S�Ẵe�N�X�`������֐�(�f�X�g���N�^�[���ɌĂ΂��)
		* @param[in] key_	�e�N�X�`���ɐݒ肳��Ă���L�[
		*/
		void AllRelease();


	private:
		/**
		* @brief �R���X�g���N�^
		*/
		TextureManager() {
		}

		/**
		* @brief �f�X�g���N�^
		*/
		~TextureManager();


		std::map<std::string, TextureData*> m_TextureMap;	//! �e�N�X�`���}�b�v

	};
}

typedef MySingletonTemplate::SingletonTemplate<MyTextureManager::TextureManager> TextureManager;
#define THE_TEXTUREMANAGER TextureManager::GetInstance()

#endif