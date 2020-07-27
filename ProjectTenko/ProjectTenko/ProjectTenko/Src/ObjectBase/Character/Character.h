#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../ObjectBase.h"
#include "../../Engine/Fbx/FbxMotion.h"

/**
* @brief キャラクターの基底クラス
*/
class Character : public ObjectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	Character(D3DXVECTOR3 pos_, std::string key_) :
		ObjectBase(pos_, key_)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~Character() {}

};

#endif