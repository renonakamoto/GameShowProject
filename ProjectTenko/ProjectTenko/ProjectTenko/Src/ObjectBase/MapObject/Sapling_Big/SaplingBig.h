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
	SaplingBig(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

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