#ifndef TREE_H_
#define TREE_H_

#include "../MapObject.h"

/**
* @brief 木クラス
*/
class Tree : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Tree(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Tree() {}

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