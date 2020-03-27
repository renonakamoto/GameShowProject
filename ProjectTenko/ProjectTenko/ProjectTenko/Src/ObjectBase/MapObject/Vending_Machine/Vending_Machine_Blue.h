#ifndef VENDING_MACHINE_BLUE_H_
#define VENDING_MACHINE_BLUE_H_

#include "../MapObject.h"

class VendingMachineBlue : public MapObject
{
public:
	VendingMachineBlue(D3DXVECTOR3 pos_, std::string key_);

	virtual ~VendingMachineBlue() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif