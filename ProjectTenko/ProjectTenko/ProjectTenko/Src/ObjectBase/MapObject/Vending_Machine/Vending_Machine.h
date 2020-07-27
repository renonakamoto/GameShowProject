#ifndef VendingMachine_H_
#define VendingMachine_H_

#include "../MapObject.h"

/**
* @brief ���̋@�N���X
*/
class VendingMachine : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	VendingMachine(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~VendingMachine(){}

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