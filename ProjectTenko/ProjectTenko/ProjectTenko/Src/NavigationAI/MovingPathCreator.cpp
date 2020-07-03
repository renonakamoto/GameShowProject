#include "MovingPathCreator.h"
#include "..//Manager/ObjectManager.h"
#include "..//Collision/FlexibleCollision.h"
#include <memory>
#include <math.h>
#include <vector>
#include <string>
#include "..//ExternalFle/Csv/Csv.h"

MovingPathCreator::MovingPathCreator()
{
}

MovingPathCreator::~MovingPathCreator()
{
}

bool MovingPathCreator::CreateMovingPath(D3DXVECTOR3 originPos_, float xzPlaneX_, float xzPlaneZ_, float cellsize_, float objectsize_, float raylength_)
{
	// 規定外の値のチェック
	if (xzPlaneX_ <= 0 || xzPlaneZ_ <= 0 || cellsize_ <= 0 || objectsize_ <= 0)
	{
		return false;
	}

	// Rayの始点をマスの中心に調整
	D3DVECTOR pos = originPos_;
	pos.x += cellsize_ / 2;
	pos.z += cellsize_ / 2;

	// フィールドの分割
	const int xz_x = static_cast<int>(xzPlaneX_ / cellsize_) + 1;
	const int xz_z = static_cast<int>(xzPlaneZ_ / cellsize_) + 1;

	// CSVに送るためにstringをvectorで作る
	std::vector<std::vector <std::string>> csvdata;

	// 一段目にフィールドのサイズを入力
	std::vector<std::string> data;
	data.push_back(std::to_string(xz_x));
	data.push_back(std::to_string(xz_z));
	csvdata.push_back(data);

	data.clear();

		// 当たり判定処理
	for (int i = 0; i < xz_z; i++)
	{
		for (int j = 0; j < xz_x; j++)
		{
			// 情報入力処理
			// マスの位置情報入力
			data.push_back(std::to_string(j));
			data.push_back(std::to_string(i));

			// 8方向へのベクトルの生成
			D3DXVECTOR3 vec[8];
			Create8Vec(pos, cellsize_, vec);

			for (int k = 0; k < 8; k++)
			{
				data.push_back(std::to_string(THE_OBJECTMANAGER->HitRayAndObject(pos, vec[k])));
			}

			csvdata.push_back(data);
			pos.x += cellsize_;
		}
		pos.x = originPos_.x + (cellsize_ / 2);
		pos.z += cellsize_;
	}

	return false;
}

void MovingPathCreator::Create8Vec(const D3DXVECTOR3 pos_, float length_, D3DXVECTOR3(&vec_)[8])
{
	// 北方向
	vec_[0] = { 0,			0,	length_ };
	// 北東方向
	vec_[1] = { length_,	0,	length_ };
	// 東方向
	vec_[2] = { length_,	0,	0 };
	// 南東方向
	vec_[3] = { length_,	0,	-length_ };
	// 南方向
	vec_[4] = { 0,			0,	-length_ };
	// 南西方向
	vec_[5] = { -length_,	0,	-length_ };
	// 西方向
	vec_[6] = { -length_,	0,	0 };
	// 北西方向
	vec_[7] = { -length_,	0,	length_ };
}
