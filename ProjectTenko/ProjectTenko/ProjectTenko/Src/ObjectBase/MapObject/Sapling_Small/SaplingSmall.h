#ifndef SAPLINGSMALL_H_
#define SAPLINGSMALL_H_

#include "../MapObject.h"

/**
* @brief �c��(��)�N���X
*/
class SaplingSmall : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SaplingSmall(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~SaplingSmall() {}

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