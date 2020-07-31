#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "../MapObject.h"

/**
* @brief �����蔻����s���I�u�W�F�N�g���Z�o����֐�
* @param[in] pOut_	     ���C�̌��_
* @param[in] basePoint_  ���C�̌����Ƒ傫��(�x�N�g��)
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