#ifndef FLEXIBLECOLLISION_H_
#define FLEXIBLECOLLISION_H_

#include "Collision.h"
#include "Shape/Shape.h"
#include <vector>

class Shape;

/**
* @brief �����蔻��Ǘ��N���X
*/
class FlexibleCollision
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FlexibleCollision();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~FlexibleCollision();

	/**
	* @brief	 �����蔻����s���֐�
	* @param[in] s1_	�����蔻����s���O���[�v
	* @param[in] s2_	�����蔻����s���O���[�v
	* @return bool true: �������� false: �������Ă��Ȃ�
	*/
	bool Test(const std::vector<Shape*>& s1_, const std::vector<Shape*>& s2_);

	/**
	* @brief	 �����蔻����s���֐�
	* @param[in] s1_	�����蔻����s���I�u�W�F�N�g
	* @param[in] s2_	�����蔻����s���I�u�W�F�N�g
	* @return bool true: �������� false: �������Ă��Ȃ�
	*/
	bool Test(const Shape& s1_, const Shape& s2_);


private:
	//! ������e�[�u��
	Collision* m_CollisionTable[static_cast<int>(SHAPE_TYPE::Shape_Type_Num)][static_cast<int>(SHAPE_TYPE::Shape_Type_Num)];
};

#endif