#ifndef BARREL_H_
#define BARREL_H_

#include "../MapObject.h"

class Barrel : public MapObject
{
public:
	Barrel(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Barrel() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif