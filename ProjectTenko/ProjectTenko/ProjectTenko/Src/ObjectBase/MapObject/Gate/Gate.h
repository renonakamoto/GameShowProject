#ifndef GATE_H_
#define GATE_H_

#include "../MapObject.h"

/**
* @brief ゲートクラス
*/
class Gate : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Gate(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Gate() {}

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