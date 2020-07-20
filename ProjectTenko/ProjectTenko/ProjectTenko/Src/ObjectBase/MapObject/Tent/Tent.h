#ifndef TENT_H_
#define TENT_H_

#include "../MapObject.h"

/**
* @brief テントクラス
*/
class Tent : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Tent(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Tent() {}

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