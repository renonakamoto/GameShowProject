#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

#include "../../Utility/SingletonTemplate.h"
#include "FbxLoader.h"
#include "FbxDrawer.h"
#include <string>
#include <map>

namespace MyFbx
{
	/**
	* @brief Fbx�������N���X
	* @details Fbx�̓ǂݍ��݂ƕ`�������
	*/
	class FbxManager
	{

		friend MySingletonTemplate::SingletonTemplate<FbxManager>;
	public:
		/**
		* @brief �ȒP�Ȑ����i�`����֐��j
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肷��L�[
		* @param[in] pFileName_ �ǂݍ��݂���FBX�̃t�@�C����(�p�X�t)
		* @return bool ����:true ���s:false
		*/
		bool LoadFBXMesh(std::string key_, const char* pFileName_);

		/**
		* @brief �ȒP�Ȑ����i�`����֐��j
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肳��Ă���L�[
		* @details �L�[�Ŏw�肵���I�u�W�F�N�g�̉��
		*/
		void ReleaseFbxMesh(std::string key_);

		/**
		* @brief ���������I�u�W�F�N�g�����ׂĉ������
		*/
		void AllReleaseFbxMesh();

		/**
		* @brief �`�悷��֐�
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肵�Ă���L�[
		*/
		void Draw(std::string key_, const D3DXMATRIX& world_);

		/**
		* @brief �A�j���[�V�����֐�
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肳��Ă���L�[
		* @param[in] sec_ 
		* @details Fbx���b�V����
		*/
		void Animation(std::string key_, float sec_);

		/**
		* @brief �ȒP�Ȑ����i�`����֐��j
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肳��Ă���L�[
		* @details Fbx���b�V����
		*/
		void ResetAnimation(std::string key_);

	private:

		FbxManager() 
		{
			if (m_FbxDrawe == nullptr)
			{
				m_FbxDrawe = new FbxDrawer();
			}

			if (m_FbxLoader == nullptr)
			{
				m_FbxLoader = new FbxLoader();
			}
		}
		
		~FbxManager()
		{
			if (m_FbxDrawe != nullptr)
			{
				delete m_FbxDrawe;
				m_FbxDrawe = nullptr;
			}

			if (m_FbxLoader != nullptr)
			{
				delete m_FbxLoader;
				m_FbxLoader = nullptr;
			}
		}

		/**
		* @brief m_ObjectMeshData�������̃L�[�������Ă��邩���ׂ�֐�
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肳��Ă���L�[
		* @return bool �����Ă���:true �����Ă��Ȃ�:false
		*/
		bool HasKey(std::string key_);

		//! �I�u�W�F�N�g��ۑ�����ϐ�
		std::map<std::string, FBXMeshData> m_ObjectMeshData;

		//! �ǂݍ��ݒS���N���X
		FbxLoader* m_FbxLoader;
		//! �`��S���N���X
		FbxDrawer* m_FbxDrawe;
	};
}


#endif