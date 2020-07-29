#ifndef VendingMachine_H_
#define VendingMachine_H_

#include "../MapObject.h"

/**
* @brief 自販機クラス
*/
class VendingMachine : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	VendingMachine(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~VendingMachine(){}

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