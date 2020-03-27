#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Character.h"

class Player : public Character
{
public:
	Player(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Player() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif