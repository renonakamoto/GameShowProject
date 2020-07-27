#ifndef BARREL_H_
#define BARREL_H_

#include "../MapObject.h"

/**
* @brief 樽クラス
*/
class Barrel : public MapObject
{
public:
	/**
	* @brief 更新関数
	*/
	Barrel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Barrel() {}

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