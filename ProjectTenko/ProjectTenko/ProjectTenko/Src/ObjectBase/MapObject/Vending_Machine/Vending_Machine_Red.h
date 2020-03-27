#ifndef VENDING_MACHINE_RED_H_
#define VENDING_MACHINE_RED_H_

#include "../MapObject.h"

class VendingMachineRed : public MapObject
{
public:
	VendingMachineRed(D3DXVECTOR3 pos_, std::string key_);

	virtual ~VendingMachineRed() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif