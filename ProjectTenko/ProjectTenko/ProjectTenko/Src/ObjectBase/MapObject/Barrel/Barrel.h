#ifndef BARREL_H_
#define BARREL_H_

#include "../MapObject.h"

/**
* @brief �M�N���X
*/
class Barrel : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Barrel(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Barrel() {}

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