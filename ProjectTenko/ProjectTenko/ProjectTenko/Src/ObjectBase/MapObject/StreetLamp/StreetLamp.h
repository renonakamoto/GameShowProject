#ifndef StreetLamp_H_
#define StreetLamp_H_

#include "../MapObject.h"

/**
* @brief �X���N���X
*/
class StreetLamp : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	StreetLamp(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~StreetLamp() {}

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