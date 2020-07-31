#ifndef SHRIMPSTATUE_H_
#define SHRIMPSTATUE_H_

#include "../MapObject.h"

/**
* @brief 海老天像クラス
*/
class ShrimpStatue : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	ShrimpStatue(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

	/**
	* @brief デストラクタ
	*/
	virtual ~ShrimpStatue() {}

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