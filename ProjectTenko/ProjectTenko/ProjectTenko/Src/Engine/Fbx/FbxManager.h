#ifndef FBXMANAGER_H_
#define FBXMANAGER_H_

#include "../../Utility/SingletonTemplate.h"
#include "FbxLoader.h"
#include "FbxDrawer.h"
#include <string>
#include <map>
#include <memory>

namespace MyFbx
{
	/**
	* @brief	Fbx�������N���X
	* @details	Fbx�̓ǂݍ��݂ƕ`�������
	*/
	class FbxManager
	{

		friend MySingletonTemplate::SingletonTemplate<FbxManager>;
	public:
		/**
		* @brief Fbx�̓ǂݍ���
		* @param[in] key_ FbxData�ɐݒ肷��L�[
		* @param[in] pFileName_ �ǂݍ��݂���FBX�̃t�@�C����(�p�X�t)
		* @return bool ����:true ���s:false
		*/
		bool LoadFBXMesh(std::string key_, const char* pFileName_);

		/**
		* @brief �w�肵��MeshData���폜
		* @param[in] key_ FbxData�ݒ肳��Ă���L�[
		* @details �L�[�Ŏw�肵���I�u�W�F�N�g�̉��
		*/
		void ReleaseFbxMesh(std::string key_);

		/**
		* @brief ���ׂĂ�MeshData���폜
		*/
		void AllReleaseFbxMesh();

		/**
		* @brief Fbx�̕`��֐�
		* @param[in] key_	FbxData�ݒ肳��Ă���L�[
		* @param[in] world_ �ǂݍ��݂���FBX�̃t�@�C����(�p�X�t)
		*/
		void Draw(std::string key_, const D3DXMATRIX& world_, UCHAR alpha_ = 255);

		/**
		* @brief �A�j���[�V�����֐�
		* @param[in] key_	FbxData�ݒ肳��Ă���L�[
		* @param[in] sec_	�L�[�t���[��
		* @details �`��֐��ł͂Ȃ��̂�Update���Ɏg�p���Ă�������
		*/
		void Animation(std::string key_, float sec_);

		/**
		* @brief �A�j���[�V�����̏�����
		* @param[in] key_ FbxData�ݒ肳��Ă���L�[
		*/
		void ResetAnimation(std::string key_);

	private:
		/**
		* @brief �R���X�g���N�^
		*/
		FbxManager();

		/**
		* @brief �f�X�g���N�^
		*/
		~FbxManager();

		/**
		* @brief m_ObjectMeshData�������̃L�[�������Ă��邩���ׂ�֐�
		* @param[in] key_ �I�u�W�F�N�g�ɐݒ肳��Ă���L�[
		* @return bool �����Ă���:true �����Ă��Ȃ�:false
		*/
		bool HasKey(std::string key_);

		//! �I�u�W�F�N�g��ۑ�����ϐ�
		std::map<std::string, FBXMeshData*> m_ObjectMeshData;

		//! �ǂݍ��ݒS���N���X
		std::unique_ptr<FbxLoader> m_FbxLoader;
		//! �`��S���N���X
		std::unique_ptr<FbxDrawer> m_FbxDrawe;
	};
}

typedef MySingletonTemplate::SingletonTemplate<MyFbx::FbxManager> FbxMeshManager;
#define THE_FBXMANAGER FbxMeshManager::GetInstance()

#endif