#ifndef WALL_H_
#define WALL_H_

#include "../MapObject.h"

/**
* @brief �ǃN���X
*/
class Wall : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Wall(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Wall() {}

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