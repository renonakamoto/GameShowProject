#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "../MapObject.h"

/**
* @brief �X�J�C�h�[���N���X
*/
class Skydome : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Skydome(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Skydome() {}

	/**
	* @brief �X�V�֐�
	*/
	virtual void Update() override;

	/**
	* @brief �`��֐�
	*/
	virtual void Draw() override;

};

#endif