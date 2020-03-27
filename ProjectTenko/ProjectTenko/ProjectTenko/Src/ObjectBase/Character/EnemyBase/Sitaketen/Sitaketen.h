#ifndef SITAKETEN_H_
#define SITAKETEN_H_

#include "../EnemyBase.h"

class Sitaketen : public Enemybase
{
public:
	Sitaketen(D3DXVECTOR3 pos_, std::string key_);

	~Sitaketen() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif