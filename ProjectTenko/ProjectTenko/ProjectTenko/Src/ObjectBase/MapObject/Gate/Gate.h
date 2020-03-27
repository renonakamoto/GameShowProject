#ifndef GATE_H_
#define GATE_H_

#include "../MapObject.h"

class Gate : public MapObject
{
public:
	Gate(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Gate() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif