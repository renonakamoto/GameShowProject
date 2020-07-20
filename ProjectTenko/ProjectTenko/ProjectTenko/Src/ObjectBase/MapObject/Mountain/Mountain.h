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
	Mountain(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

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