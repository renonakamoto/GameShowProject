#ifndef WALL_H_
#define WALL_H_

#include "../MapObject.h"

/**
* @brief 壁クラス
*/
class Wall : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Wall(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Wall() {}

	/**
	* @brief 更新関数
	*/
	virtual void Update() override;

	/**
	* @brief 描画関数
	*/
	virtual void Draw() override;

};

#endif