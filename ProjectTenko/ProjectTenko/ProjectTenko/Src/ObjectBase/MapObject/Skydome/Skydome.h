#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "../MapObject.h"

/**
* @brief 当たり判定を行うオブジェクトを算出する関数
* @param[in] pOut_	     レイの原点
* @param[in] basePoint_  レイの向きと大きさ(ベクトル)
*/
class Skydome : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Skydome(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Skydome() {}

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