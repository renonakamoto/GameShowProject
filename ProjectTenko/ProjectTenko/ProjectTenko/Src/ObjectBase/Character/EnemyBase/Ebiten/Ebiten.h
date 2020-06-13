#ifndef EBITEN_H_
#define EBITEN_H_

#include "../EnemyBase.h"

class Ebiten : public Enemybase
{
public:
	Ebiten(D3DXVECTOR3 pos_, const ObjectBase* 
		_, std::string key_);

	~Ebiten() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif