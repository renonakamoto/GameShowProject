#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "../MapObject.h"

/**
* @brief スカイドームクラス
*/
class Skydome : public MapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Skydome(std::vector<MapObjectData>* mapObjcectList_, const std::string& key_);

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