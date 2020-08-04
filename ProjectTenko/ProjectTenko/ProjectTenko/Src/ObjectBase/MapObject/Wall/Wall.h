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
	Wall(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

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