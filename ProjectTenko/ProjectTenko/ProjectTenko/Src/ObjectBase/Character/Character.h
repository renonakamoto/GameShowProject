#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../ObjectBase.h"
#include "../../Engine/Fbx/FbxMotion.h"

class Character : public ObjectBase
{
public:
	Character(D3DXVECTOR3 pos_, std::string key_) :
		ObjectBase(pos_, key_)
	{}
	virtual ~Character() {}


protected:


private:

};

#endif