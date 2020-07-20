#ifndef TREE_H_
#define TREE_H_

#include "../MapObject.h"

/**
* @brief �؃N���X
*/
class Tree : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Tree(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Tree() {}

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