#ifndef MERRYGOLAND_H_
#define MERRYGOLAND_H_

#include "../MapObject.h"

/**
* @brief メリーゴーランドクラス
*/
class Merrygoland : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Merrygoland(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Merrygoland() {}

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