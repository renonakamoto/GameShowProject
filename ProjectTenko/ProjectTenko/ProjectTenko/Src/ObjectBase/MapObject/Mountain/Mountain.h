#ifndef MOUNTAIN_H_
#define MOUNTAIN_H_

#include "../MapObject.h"

class Mountain : public MapObject
{
public:
	Mountain(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Mountain() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif