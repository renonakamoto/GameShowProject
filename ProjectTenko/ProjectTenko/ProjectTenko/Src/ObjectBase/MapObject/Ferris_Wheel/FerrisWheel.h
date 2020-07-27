#ifndef FERRISWHEEL_H_
#define FERRISWHEEL_H_

#include "../MapObject.h"

/**
* @brief 観覧車クラス
*/
class FerrisWheel : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	FerrisWheel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~FerrisWheel() {}

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