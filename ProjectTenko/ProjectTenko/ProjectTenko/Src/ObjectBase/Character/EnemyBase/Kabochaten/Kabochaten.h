#ifndef KABOCHATEN_H_
#define KABOCHATEN_H_

#include "../EnemyBase.h"

class Kabochaten : public Enemybase
{
public:
	Kabochaten(D3DXVECTOR3 pos_, std::string key_);

	~Kabochaten() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif