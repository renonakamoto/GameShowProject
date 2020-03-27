#ifndef TENT_H_
#define TENT_H_

#include "../MapObject.h"

class Tent : public MapObject
{
public:
	Tent(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Tent() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif