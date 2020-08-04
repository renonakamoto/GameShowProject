#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "../Utility/SingletonTemplate.h"

/**
* @brief �Q�[���̐ݒ�Ǘ��N���X
* @details 
*/
class GameConfigManager
{
	friend MySingletonTemplate::SingletonTemplate<GameConfigManager>;
public:
	
	/**
	* @brief �{�^���������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] flip �}�E�X�𔽓]������ : true�@�}�E�X�𔽓]�����Ȃ� : false
	*/
	void SetMouseFlip(bool flip) { m_IsMouseFlip = flip; }

	/**
	* @brief �}�E�X�����]���Ă��邩�ǂ�����Ԃ�
	* @return bool �}�E�X���]���Ă���:true �}�E�X���]���Ă��Ȃ�:false
	*/
	bool IsMouseFlip()const		 { return m_IsMouseFlip; }
	
private:

	/**
	* @brief �R���X�g���N�^
	*/
	GameConfigManager()
	{
		m_IsMouseFlip = false;
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~GameConfigManager(){}


	bool m_IsMouseFlip;	//! �}�E�X�̔��]����ۑ�����ϐ�
	


};

typedef MySingletonTemplate::SingletonTemplate<GameConfigManager> ConfigManager;
#define THE_CONFIGMANAGER ConfigManager::GetInstance()

#endif