#ifndef TENT_H_
#define TENT_H_

#include "../MapObject.h"

/**
* @brief �e���g�N���X
*/
class Tent : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Tent(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Tent() {}

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