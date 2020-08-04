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

/**
* @brief �I�u�W�F�N�g�Ǘ��N���X
*/
class Objectmanager
{

	friend MySingletonTemplate::SingletonTemplate<Objectmanager>;
public:
	/**
	* @brief �I�u�W�F�N�g�̎�ޗ�
	*/
	enum class ObjectType
	{
		Player,				//! �v���C���[
		Enemy,				//! �G�l�~�[
		Camera,				//! �J����
		MapObject,			//!	�}�b�v�I�u�W�F�N�g

		TypeNum,			//! �^�C�v�̐�
	};

public:
	
	/**
	* @brief �I�u�W�F�N�g�̍X�V�֐�
	*/
	void Update();

	/**
	* @brief �I�u�W�F�N�g�̕`��֐��j
	*/
	void Draw();
	
	void EntryObject(ObjectType type_);

	void ExitObject(ObjectType type_);

	void AllRelease();

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
		if (m_Camera == nullptr)
		{
			new Camera();
		}
		return m_Camera;
	}

private:
	/**
	* @brief �R���X�g���N�^
	*/
	Objectmanager();

	/**
	* @brief �f�X�g���N�^
	*/
	~Objectmanager();

	/**
	* @brief �����蔻����s���I�u�W�F�N�g���Z�o����֐�
	* @param[out] pOut_	     �����蔻����s���I�u�W�F�N�g
	* @param[in] basePoint_  �I�u�W�F�N�g�̍��W
	*/
	void JudgementCollition(std::vector<Shape*>* pOut_, const D3DXVECTOR3& basePoint_, float length);

	/**
	* @brief �v���C���[�����֐�
	*/
	void CreatePlayer();

	/**
	* @brief �G�����֐�
	*/
	void CreateEnemies();

	/**
	* @brief �}�b�v�����֐�
	*/
	void CreateMap();
	

	ObjectBase* m_Player;							//! �v���C���[
	std::vector<ObjectBase*> m_EnemyGroup;			//! �G�l�~�[�O���[�v
	std::vector<ObjectBase*> m_Object;				//! �����蔻��̂Ȃ��I�u�W�F�N�g�O���[�v
	std::vector<ObjectBase*> m_MapObjectGroup;		//! �����蔻��̂���I�u�W�F�N�g�O���[�v

	Camera* m_Camera;	

	FlexibleCollision m_Collision;
	std::unique_ptr<MapDataBank> m_MapDataBank;
	
};

typedef MySingletonTemplate::SingletonTemplate<Objectmanager> ObjectManager;
#define THE_OBJECTMANAGER ObjectManager::GetInstance()

#endif