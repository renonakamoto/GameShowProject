#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "../MapObject.h"

class Skydome : public MapObject
{
public:
	Skydome(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Skydome() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif