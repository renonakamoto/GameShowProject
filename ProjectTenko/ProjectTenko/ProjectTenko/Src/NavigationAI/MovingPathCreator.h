#ifndef MOVINGPATHCREATOR
#define MOVINGPATHCREATOR

#include "..//Collision/FlexibleCollision.h"
#include <vector>

struct PathInfo
{
	unsigned m_x;			//!< �Z����̈ʒux 
	unsigned m_z;			//!< �Z����̈ʒuz
	bool MovableInfo[8];	//!< ����8�����̃}�X�ւ̈ړ��̉ہAz+������0�Ƃ��Ď��v���Ɋi�[
};

class MovingPathCreator
{
public:
	MovingPathCreator();
	~MovingPathCreator();

	/**
	* @biref �}�b�v�̈ړ��\�o�H�����쐬���܂�
	*/
	bool CreateMovingPath(D3DXVECTOR3 lefttop_, float fieldwidth_, float fieldheight_, float cellsize_, float objectsize_, float raylength_);

private:
	/**
	* @biref 8�����ւ̃x�N�g�����Z�o����֐�
	* @param[in]	pos_	�x�N�g���̎n�_
	* @param[in]	length_ �ׂƂ̋���
	* @param[out]	 vec_	�Z�o�����x�N�g�����i�[����ϐ�
	*/
	void Create8Vec(const D3DXVECTOR3 pos_, float length_, D3DXVECTOR3 (&vec_)[8]);
};

#endif // !MOVINGPATHCREATOR
