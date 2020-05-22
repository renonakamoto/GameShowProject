#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "../ObjectBase.h"
#include <vector>

struct MapObjectData
{
	MapObjectData()
	{}
	MapObjectData(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 rot_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_)
	{}

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Rot;

};

class MapObject : public ObjectBase
{
public:
	MapObject(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
		ObjectBase(pos_, key_),
		m_MapObjectDataList(mapObjcectList_)
	{}
	virtual ~MapObject() {}

protected:
	std::vector<MapObjectData> m_MapObjectDataList;
		 
private:

};

#endif