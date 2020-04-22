#ifndef SCENE_H_
#define SCENE_H_

#include <Windows.h>
#include "SceneDefinition.h"
#include "SceneChanger.h"

class Scene
{
public:
	/**
	* @biref �R���X�g���N�^
	* @param[in] sceneChanger_ �V�[���ύX�̂��߂̃C���^�[�t�F�C�X(SceneManager)�̃|�C���^
	*/
	Scene(SceneChanger* sceneChanger_) :
		m_SceneChanger(sceneChanger_),
		m_CurrentState(SceneState::Init),
		m_ThreadHandle(nullptr),
		m_dwThreadID(0)
	{	}

	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~Scene() {	}

	/**
	* @biref �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @biref �`��֐�
	*/
	virtual void Draw() {	};
	
protected:

	/**
	* @biref Main�����֐�
	*/
	virtual void Main() = 0;

	/**
	* @brief Loading�����֐�
	*/
	virtual void Load() = 0;

	virtual DWORD WINAPI LoadResources(LPVOID lpParam_) = 0;

protected:
	SceneChanger* m_SceneChanger;	//!< �V�[���ύX�̂��߂̃C���^�[�t�F�C�X��ێ�����|�C���^
	SceneState m_CurrentState;		//!< ���݂̃V�[���̏��
	HANDLE m_ThreadHandle;			//!< �}���`�X���b�h�p�̃n���h���ۑ��ϐ�
	DWORD m_dwThreadID;				//!< �}���`�X���b�h�p�̃X���b�hID
};

#endif // !SCENE_H_