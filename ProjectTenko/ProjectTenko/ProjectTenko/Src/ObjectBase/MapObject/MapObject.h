#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "../ObjectBase.h"

class MapObject : public ObjectBase
{
public:
	MapObject(D3DXVECTOR3 pos_, std::string key_) :
		ObjectBase(pos_, key_)
	{}
	virtual ~MapObject() {}

protected:

private:

};

#endif