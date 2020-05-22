#ifndef FERRISWHEEL_H_
#define FERRISWHEEL_H_

#include "../MapObject.h"

class FerrisWheel : public MapObject
{
public:
	FerrisWheel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~FerrisWheel() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

};

#endif