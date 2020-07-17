#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../../Camera/Camera.h"
#include "../Character.h"
#include "PlayerEffect.h"
#include "State/PlayerStateBase.h"

class Player : public Character
{
public:
	Player(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Player();

	/**
	* @brief �X�V�֐�
	*/
	virtual void Update() override;

	/**
	* @brief �`��֐�
	*/
	virtual void Draw()   override;

	/**
	* @brief		
	* @return bool	�}�E�X���]���Ă���:true �}�E�X���]���Ă��Ȃ�:
	*/
	bool IsMove() { return m_IsMove; }

	/**
	* @brief		���[�V�����֐�
	* @details		PlayerState�Ŏg��
	* @param[in]	motionId_	���[�V����ID
	* @param[in]	isLoop_		true: ���[�v������ false: ���[�v�����Ȃ�
	* @param[in]	*isEnd_		true: ���Ⴊ��ł��� false: ���Ⴊ��ł��Ȃ�
	*/
	void Motion(PlayerMotionList motionId_, bool isLoop_ = true, bool* isEnd_ = nullptr);

	/**
	* @brief			��ԑJ�ڊ֐�
	* @details			PlayerState�Ŏg��
	* @param[in] state_	�J�ڂ��������
	*/
	void ChangeState(PlayerStateBase* state_);

	/**
	* @brief		�Z�b�^�[
	* @details		PlayerState�Ŏg��
	* @param[in]	isSquad_	 true: ���Ⴊ��ł��� false: ���Ⴊ��ł��Ȃ�
	*/
	void SetIsSquad(bool isSquad_) { m_IsSquat = isSquad_; }

private:
	/**
	* @brief �ړ�����
	*/
	void Move();

	Camera* m_RefCamera;					//! �J�����̎Q�Ɨp�ϐ�

	float m_WalkSpeed;						//! �����Ă��Ԃł̃X�s�[�h
	float m_SquatWalkSpeed;					//! ���Ⴊ��ł��Ԃł̃X�s�[�h

	bool m_IsSquat;							//! ���Ⴊ��ł��邩�ǂ����ۑ�����ϐ�
	bool m_IsMove;							//! �����Ă��邩�ǂ�����ۑ�����ϐ�

	D3DXVECTOR3 m_CenterPos;				//! �v���C���[�̒��S�_(���Ⴊ�񂾎��ɃJ�����������邽�߂ɒǉ�)

	FbxMotion<PlayerMotionList> m_Motion;	//! ���[�V�����N���X
	PlayerStateBase* m_State;				//! �v���C���[��ԊǗ��N���X

	PlayerEffect*	 m_PlayerEffect;		//! �G�t�F�N�g�N���X
	
};

#endif