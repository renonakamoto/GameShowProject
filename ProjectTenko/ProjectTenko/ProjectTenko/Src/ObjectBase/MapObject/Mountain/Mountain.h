#ifndef MOUNTAIN_H_
#define MOUNTAIN_H_

#include "../MapObject.h"

/**
* @brief �R�N���X
*/
class Mountain : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Mountain(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Mountain() {}

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