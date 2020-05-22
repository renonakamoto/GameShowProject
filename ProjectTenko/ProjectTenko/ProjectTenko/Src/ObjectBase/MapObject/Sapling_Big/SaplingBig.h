#ifndef SAPLINGBIG_H_
#define SAPLINGBIG_H_

#include "../MapObject.h"

class SaplingBig : public MapObject
{
public:
	SaplingBig(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~SaplingBig() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

};

#endif