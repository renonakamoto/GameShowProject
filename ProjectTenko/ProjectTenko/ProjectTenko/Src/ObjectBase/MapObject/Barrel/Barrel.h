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
	* @brief �X�V�֐�
	*/
	Barrel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

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