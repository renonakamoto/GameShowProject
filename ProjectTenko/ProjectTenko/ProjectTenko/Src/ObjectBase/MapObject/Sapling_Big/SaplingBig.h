#ifndef SAPLINGBIG_H_
#define SAPLINGBIG_H_

#include "../MapObject.h"

/**
* @brief 苗木(大)クラス
*/
class SaplingBig : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	SaplingBig(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~SaplingBig() {}

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