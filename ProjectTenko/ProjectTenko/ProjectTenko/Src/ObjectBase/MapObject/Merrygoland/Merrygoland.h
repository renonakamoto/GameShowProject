#ifndef MERRYGOLAND_H_
#define MERRYGOLAND_H_

#include "../MapObject.h"

/**
* @brief �����[�S�[�����h�N���X
*/
class Merrygoland : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Merrygoland(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Merrygoland() {}

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