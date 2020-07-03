#ifndef BARREL_H_
#define BARREL_H_

#include "../MapObject.h"

class Barrel : public MapObject
{
public:
	Barrel(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~Barrel() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

	// TODO バレルの大きさを図る
	// TODO バレルの当たり判定の改良

};

#endif