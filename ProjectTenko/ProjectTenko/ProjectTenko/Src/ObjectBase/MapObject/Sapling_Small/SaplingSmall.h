#ifndef SAPLINGSMALL_H_
#define SAPLINGSMALL_H_

#include "../MapObject.h"

class SaplingSmall : public MapObject
{
public:
	SaplingSmall(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~SaplingSmall() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

};

#endif