#ifndef MOUNTAIN_H_
#define MOUNTAIN_H_

#include "../MapObject.h"

/**
* @brief 山クラス
*/
class Mountain : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Mountain(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Mountain() {}

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