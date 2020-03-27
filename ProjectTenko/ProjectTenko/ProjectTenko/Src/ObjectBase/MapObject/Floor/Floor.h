#ifndef FLOOR_H_
#define FLOOR_H_

#include "../MapObject.h"

class Floor : public MapObject
{
public:
	Floor(D3DXVECTOR3 pos_, std::string key_);

	virtual ~Floor() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif