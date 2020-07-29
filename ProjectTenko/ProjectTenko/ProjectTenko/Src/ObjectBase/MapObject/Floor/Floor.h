#ifndef FLOOR_H_
#define FLOOR_H_

#include "../MapObject.h"

/**
* @brief 床クラス
*/
class Floor : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Floor(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Floor() {}

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