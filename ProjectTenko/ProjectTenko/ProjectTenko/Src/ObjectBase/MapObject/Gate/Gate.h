#ifndef GATE_H_
#define GATE_H_

#include "../MapObject.h"

/**
* @brief �Q�[�g�N���X
*/
class Gate : public MapObject
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Gate(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~Gate() {}

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