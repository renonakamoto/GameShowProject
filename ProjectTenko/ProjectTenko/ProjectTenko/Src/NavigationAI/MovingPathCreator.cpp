#include "MovingPathCreator.h"
#include "..//Manager/ObjectManager.h"
#include "..//Collision/FlexibleCollision.h"
#include <memory>
#include <math.h>
#include <vector>

MovingPathCreator::MovingPathCreator()
{
}

MovingPathCreator::~MovingPathCreator()
{
}

bool MovingPathCreator::CreateMovingPath(D3DXVECTOR3 originPos_, float xzPlaneX_, float xzPlaneZ_, float cellsize_, float objectsize_, float raylength_)
{
	// �K��O�̒l�̃`�F�b�N
	if (xzPlaneX_ <= 0 || xzPlaneZ_ <= 0 || cellsize_ <= 0 || objectsize_ <= 0)
	{
		return false;
	}

	// Ray�̎n�_���}�X�̒��S�ɒ���
	D3DVECTOR pos = originPos_;
	pos.x += cellsize_ / 2;
	pos.z += cellsize_ / 2;

	// �t�B�[���h�̕���
	const int xz_x = static_cast<int>(xzPlaneX_ / cellsize_) + 1;
	const int xz_z = static_cast<int>(xzPlaneZ_ / cellsize_) + 1;

	// �t�B�[���h���̊i�[�z��
	std::unique_ptr<std::unique_ptr<PathInfo[]>[]> p_info = std::make_unique<std::unique_ptr<PathInfo[]>[]>(xz_x);
	
	std::vector<std::vector<std::string>> pathfile;
	
	for (int i = 0; i < xz_z; i++)
	{
		p_info[i] = std::make_unique<PathInfo[]>(xz_z);
	}

	// �����蔻�菈��
	for (int i = 0; i < xz_x; i++)
	{
		for (int j = 0; j < xz_z; j++)
		{
			// �����͏���
			// �}�X�̈ʒu������
			p_info[i][j].m_x = j;
			p_info[i][j].m_z = i;

			//pathfile.push_back();

			// 8�����ւ̃x�N�g���̐���
			D3DXVECTOR3 vec[8];
			Create8Vec(pos, cellsize_, vec);

			for (int k = 0; k < 8; k++)
			{
				p_info[i][j].MovableInfo[k] = THE_OBJECTMANAGER->HitRayAndObject(pos, vec[k]);
			}

			pos.x += cellsize_;
		}
		pos.x = originPos_.x + (cellsize_ / 2);
		pos.z += cellsize_;
	}

	return false;
}

void MovingPathCreator::Create8Vec(const D3DXVECTOR3 pos_, float length_, D3DXVECTOR3(&vec_)[8])
{
	// �k����
	vec_[0] = { 0,			0,	length_ };
	// �k������
	vec_[1] = { length_,	0,	length_ };
	// ������
	vec_[2] = { length_,	0,	0 };
	// �쓌����
	vec_[3] = { length_,	0,	-length_ };
	// �����
	vec_[4] = { 0,			0,	-length_ };
	// �쐼����
	vec_[5] = { -length_,	0,	-length_ };
	// ������
	vec_[6] = { -length_,	0,	0 };
	// �k������
	vec_[7] = { -length_,	0,	length_ };
}
