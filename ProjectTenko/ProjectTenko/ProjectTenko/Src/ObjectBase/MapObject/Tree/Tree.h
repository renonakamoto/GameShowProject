#ifndef TREE_H_
#define TREE_H_

#include "../MapObject.h"

class Tree : public MapObject
{
public:
	Tree(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_);

	virtual ~Tree() {}

	virtual void Update() override;
	virtual void Draw() override;

private:

};

#endif