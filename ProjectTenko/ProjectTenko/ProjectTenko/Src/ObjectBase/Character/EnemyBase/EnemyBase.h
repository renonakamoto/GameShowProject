#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include <vector>
#include <d3dx9.h>

#include "../Player/Player.h"
#include "../Character.h"
#include "EnemyAI/State.h"
#include "..//..//..//NavigationAI/NavigationAI.h"
#include "..//..//..//Manager/ObjectManager.h"

#define ENEMY_VIEW 300.0f
#define ENEMY_VIEW_ANGLE 100.0f
#define ENEMY_ROTATE 0.026f

class State;

class Enemybase : public Character
{
public:
	/**
	* @biref �R���X�g���N�^
	* @param[in] pos_ ���������̍��W
	* @param[in] player_ �v���C���[�̃|�C���^
	* @param[in] key_ FBX�̃L�[
	*/
	Enemybase(D3DXVECTOR3 pos_,const ObjectBase* player_ ,std::string key_):
		m_RefPlayer(player_),
		Character(pos_, key_),
		m_State(nullptr),
		m_NextRoute(0.0f, 0.0f, 0.0f),
		m_NextRouteNum(0),
		m_NextAngle(0.0f),
		m_Speed(0.35f),
		m_IsThinking(false),
		m_Handle(nullptr),
		m_IsClockwise(false)
	{}

	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~Enemybase() {}

	/**
	* @biref �����Ԃ̈ړ������֐�
	*/
	virtual void Patrol() {}
	
	/**
	* @biref ���񒆂̕����]�������֐�
	*/
	virtual void Turn() {}

	/**
	* @biref �v���C���[�̒ǐՏ�ԏ����֐�
	*/
	virtual void Chase(){}

	/**
	* @biref ����o�H�ɕ��A����ۂ̈ړ������֐�
	*/
	virtual void Return(){}
	
	/**
	* @biref ����o�H�ɕ��A���邽�߂̌o�H�T���֐�
	*/
	virtual void Thinking(){}
	
	virtual void Attack(){}

	/**
	* @biref ���W�ύX�֐�
	*/
	virtual void Move() {}

	/**
	* @biref �ŒZ�̏��񃋁[�g�𒲂ׂ�֐�
	* ���񃋁[�g�ɕ��A����ہA�ł��߂����񃋁[�g�𒲂ׂ�֐�
	*/
	void DecideReturnPoint();
	
	/**
	* @biref �v���C���[�̒T�m�֐�
	* ���E���Ƀv���C���[�����邩�̔���֐�
	* @return �v���C���[������ꍇtrue, ���Ȃ��ꍇ��false
	*/
	bool CanDetectPC();

protected:
	State* m_State;			//!< ���݂̏��
	std::vector<D3DXVECTOR3> m_PatrolRoute;	//!< ���񃋁[�g�i�[�R���e�i
	D3DXVECTOR3 m_NextRoute;	//!< ���̖ړI���W
	unsigned m_NextRouteNum;	//!< ���̏��񃋁[�g�̔ԍ�

	float m_Speed;	//!< �ړ����x
	float m_NextAngle;	//!< ���̌���
	D3DXVECTOR3 m_MovingVector;	//!< �ړ��x�N�g��
	bool m_IsClockwise;	//!< ���̌��������v��肩�ۂ�

	NavData m_NavData;	//!< �o�H�T���p�̃f�[�^�\����
	bool m_IsThinking;  //!< �o�H�T�������ۂ�

	const ObjectBase* m_RefPlayer;		//!< �v���C���[�̎Q�Ɨp�ϐ�

	HANDLE m_Handle;	//!< �o�H�T�������̃X���b�h�n���h��
private:
};

#endif