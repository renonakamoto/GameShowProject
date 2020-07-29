#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../ObjectBase.h"
#include "../../Engine/Fbx/FbxMotion.h"

/**
* @brief �L�����N�^�[�̊��N���X
*/
class Character : public ObjectBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Character(D3DXVECTOR3 pos_, std::string key_) :
		ObjectBase(pos_, key_)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Character() {}

};

#endif