#ifndef SAPLINGBIG_H_
#define SAPLINGBIG_H_

#include "../MapObject.h"

/**
* @brief �c��(��)�N���X
*/
class SaplingBig : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SaplingBig(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~SaplingBig() {}

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