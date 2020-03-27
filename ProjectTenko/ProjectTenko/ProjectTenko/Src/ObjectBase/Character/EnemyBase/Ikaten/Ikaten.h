#ifndef IKATEN_H_
#define IKATEN_H_

#include "../EnemyBase.h"

class Ikaten : public Enemybase
{
public:
	Ikaten(D3DXVECTOR3 pos_, std::string key_);

	~Ikaten() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif