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
		ObjectBase(pos_),
		m_FbxKey(key_)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~Character() {}

protected:
	//! ワールド行列
	D3DXMATRIX  m_Mat_World;

	//! Fbxキー
	std::string m_FbxKey;

};

#endif