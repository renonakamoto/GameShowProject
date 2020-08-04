#ifndef StreetLamp_H_
#define StreetLamp_H_

#include "../MapObject.h"

/**
* @brief 街灯クラス
*/
class StreetLamp : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	StreetLamp(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief デストラクタ
	*/
	virtual ~StreetLamp() {}

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