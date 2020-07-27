#ifndef FLOOR_H_
#define FLOOR_H_

#include "../MapObject.h"

/**
* @brief ���N���X
*/
class Floor : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Floor(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Floor() {}

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