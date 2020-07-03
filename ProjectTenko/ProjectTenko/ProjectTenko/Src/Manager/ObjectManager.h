#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "../Utility/SingletonTemplate.h"
#include "../../Src/ObjectBase/ObjectBase.h"
#include "../Camera/Camera.h"
#include "../Collision/FlexibleCollision.h"
#include "../ObjectBase/MapObject/MapDataBank.h"
#include <vector>
#include <iostream>
#include <memory>

class Objectmanager
{

	friend MySingletonTemplate::SingletonTemplate<Objectmanager>;
public:
	
	/**
	* @brief �I�u�W�F�N�g�̍X�V�֐�
	*/
	void Update();

	/**
	* @brief �I�u�W�F�N�g�̕`��֐��j
	*/
	void Draw();

	/**
	* @brief �v���C���[�ƃ}�b�v��Q���Ƃ̓����蔻��֐�
	* @return bool ��������:true �������Ă��Ȃ�:false
	*/
	bool HitPlayerAndMapObject();

	/**
	* @brief �v���C���[�ƃG�l�~�[�Ƃ̓����蔻��֐�
	* @return bool ��������:true �������Ă��Ȃ�:false
	*/
	bool HitPlayerAndEnemy();

	/**
	* @brief �J�����ƃ}�b�v��Q���Ƃ̓����蔻��֐�
	* @return bool ��������:true �������Ă��Ȃ�:false
	*/
	bool HitCameraAndObject();

	/**
	* @brief �v���C���[�ƃN���A�g���K�[�Ƃ̓����蔻��֐�
	* @return bool ��������:true �������Ă��Ȃ�:false
	*/
	bool HitPlayerAndClearTrigger();

	/**
	* @brief ���C�ƃI�u�W�F�N�g�Ƃ̓����蔻��
	* @param[in] origin_ ���C�̌��_
	* @param[in] delta_  ���C�̌����Ƒ傫��(�x�N�g��)
	* @return bool ����:true ���s:false
	*/
	bool HitRayAndObject(const D3DXVECTOR3& origin_, const D3DXVECTOR3& delta_);



	Camera* GetCameraInstance()const {
		if (!m_Camera) { return nullptr; }
		return m_Camera;
	}

	void AllRelease();

private:
	Objectmanager();
	~Objectmanager();

	/*
		�����蔻����s���I�u�W�F�N�g���Z�o����֐�
	*/
	void JudgementCollition(std::vector<Shape*>* pOut_, const D3DXVECTOR3& basePoint_, float length);
	

	ObjectBase* m_Player;
	std::vector<ObjectBase*> m_Object;
	std::vector<ObjectBase*> m_EnemyGroup;
	std::vector<ObjectBase*> m_MapObjectGroup;

	Camera* m_Camera;

	FlexibleCollision m_Collision;
	MapDataBank m_MapDataBank;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif