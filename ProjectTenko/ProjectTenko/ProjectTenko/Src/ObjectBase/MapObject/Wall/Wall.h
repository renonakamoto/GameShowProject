#ifndef WALL_H_
#define WALL_H_

#include "../MapObject.h"

class Wall : public MapObject
{
public:
	Wall(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~Wall() {}

	virtual void Update() override;
	virtual void Draw() override;

protected:

private:

};

#endif