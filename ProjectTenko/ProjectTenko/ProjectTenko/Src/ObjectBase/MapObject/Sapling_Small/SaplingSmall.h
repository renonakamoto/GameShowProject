#ifndef SAPLINGSMALL_H_
#define SAPLINGSMALL_H_

#include "../MapObject.h"

/**
* @brief 苗木(小)クラス
*/
class SaplingSmall : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	SaplingSmall(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~SaplingSmall() {}

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