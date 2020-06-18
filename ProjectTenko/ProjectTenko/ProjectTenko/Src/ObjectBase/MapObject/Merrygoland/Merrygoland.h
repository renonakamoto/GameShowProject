#ifndef MERRYGOLAND_H_
#define MERRYGOLAND_H_

#include "../MapObject.h"

class Merrygoland : public MapObject
{
public:
	Merrygoland(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~Merrygoland() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif