#ifndef SHRIMPSTATUE_H_
#define SHRIMPSTATUE_H_

#include "../MapObject.h"

/**
* @brief �C�V�V���N���X
*/
class ShrimpStatue : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ShrimpStatue(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~ShrimpStatue() {}

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