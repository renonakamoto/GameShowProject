#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#include "../../ObjectManager/GameObject.h"
#include "Enemy.h"

/**
* @brief �G�l�~�[�Ǘ��N���X
*/
class EnemyManager : public ShadowMapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	EnemyManager()
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~EnemyManager()
	{
		Release();
	}
	
	/**
	* @fn void Init()
	* @brief �������֐�
	* @details �G�l�~�[�̐����A���������s��
	*/
	void Init() override;

	/**
	* @fn void Update()
	* @brief �X�V�֐�
	* @details �G�l�~�[���X�g�̍X�V���s��
	*/
	void Update() override;

	/**
	* @fn void Draw()
	* @brief �`��֐�
	* @details �Ǘ�����Ă���G�l�~�[�̕`����s��
	*/
	void Draw() override;

	/**
	* @fn void Draw()
	* @brief �V���h�E�}�b�v�`��֐�
	* @details �Ǘ�����Ă���G�l�~�[�̃V���h�E�}�b�v�`����s��
	*/
	void DrawShadowMap() override;

private:
	/**
	* @fn void Erase(int idx_)
	* @brief ���X�g����w�肵���v�f�ԍ��̃G�l�~�[���폜����֐�
	* @param[in] idx_ �폜�������G�l�~�[�̗v�f�ԍ�
	*/
	void Erase(int idx_);

	/**
	* @fn void Release()
	* @brief ����֐�
	*/
	void Release();

private:
	std::vector<Enemy*> m_Enemies;	//! �G�l�~�[�z��
	
};

#endif