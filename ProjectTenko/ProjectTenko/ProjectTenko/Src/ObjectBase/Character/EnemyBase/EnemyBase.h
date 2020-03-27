#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Character.h"

class Enemybase : public Character
{
public:
	Enemybase(D3DXVECTOR3 pos_, std::string key_):
		Character(pos_, key_)
	{}

	virtual ~Enemybase() {}

protected:

private:

};

#endif