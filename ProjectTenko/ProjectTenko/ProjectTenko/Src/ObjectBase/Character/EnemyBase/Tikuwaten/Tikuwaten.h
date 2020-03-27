#ifndef TIKUWATEN_H_
#define TIKUWATEN_H_

#include "../EnemyBase.h"

class Tikuwaten : public Enemybase
{
public:
	Tikuwaten(D3DXVECTOR3 pos_, std::string key_);
	virtual ~Tikuwaten() {}

	virtual void Update() override;
	virtual void Draw() override;

private:


};

#endif