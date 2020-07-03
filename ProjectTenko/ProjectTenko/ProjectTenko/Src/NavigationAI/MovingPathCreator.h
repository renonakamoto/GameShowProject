#ifndef MOVINGPATHCREATOR
#define MOVINGPATHCREATOR

#include "..//Collision/FlexibleCollision.h"
#include <vector>

struct PathInfo
{
	unsigned m_x;			//!< セル上の位置x 
	unsigned m_z;			//!< セル上の位置z
	bool MovableInfo[8];	//!< 周囲8方向のマスへの移動の可否、z+方向を0として時計回りに格納
};

class MovingPathCreator
{
public:
	MovingPathCreator();
	~MovingPathCreator();

	/**
	* @biref マップの移動可能経路情報を作成します
	*/
	bool CreateMovingPath(D3DXVECTOR3 lefttop_, float fieldwidth_, float fieldheight_, float cellsize_, float objectsize_, float raylength_);

private:
	/**
	* @biref 8方向へのベクトルを算出する関数
	* @param[in]	pos_	ベクトルの始点
	* @param[in]	length_ 隣との距離
	* @param[out]	 vec_	算出したベクトルを格納する変数
	*/
	void Create8Vec(const D3DXVECTOR3 pos_, float length_, D3DXVECTOR3 (&vec_)[8]);
};

#endif // !MOVINGPATHCREATOR
