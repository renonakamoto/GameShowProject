#ifndef SHRIMPSTATUE_H_
#define SHRIMPSTATUE_H_

#include "../MapObject.h"

class ShrimpStatue : public MapObject
{
public:
	ShrimpStatue(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~ShrimpStatue() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

};

#endif