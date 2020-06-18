#ifndef DEBUGSCENE_H_
#define DEBUGSCENE_H_

#include "SceneChanger.h"
#include <stack>
#include <memory>

class DebugScene : public SceneChanger
{
public:
	DebugScene(SceneChanger* sceneChanger_);
	virtual ~DebugScene();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @biref �`��֐�
	*/
	void Draw();

	/**
	* @biref �V�[���ύX�֐�
	*/
	void ChangeScene(SceneID id_) override;

	/**
	* @biref �V�[���ǉ��֐�
	*/
	void PushScene(SceneID id_) override;

	/**
	* @biref �V�[���폜�֐�
	*/
	void PopScene() override;

private:
	std::stack<std::unique_ptr<Scene>> m_SceneList;		//!< ���g�����������V�[���ێ��ϐ�
	SceneChanger* m_SceneChanger;						//!< �V�[���}�l�[�W���[�ւ�I/F
};

#endif // !DEBUGSCENE_H_
