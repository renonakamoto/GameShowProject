#ifndef FERRISWHEEL_H_
#define FERRISWHEEL_H_

#include "../MapObject.h"

/**
* @brief �ϗ��ԃN���X
*/
class FerrisWheel : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FerrisWheel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~FerrisWheel() {}

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