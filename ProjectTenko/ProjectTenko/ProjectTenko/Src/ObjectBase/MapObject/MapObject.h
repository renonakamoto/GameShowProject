#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "../ObjectBase.h"
#include "../MapObject/MapDataBank.h"
#include <vector>


struct MapObjectData
{
	/**
	* @brief	コンストラクタ
	*/
	MapObjectData() :
		m_Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Width(0.0f),
		m_Height(0.0f),
		m_Depth(0.0f)
	{}

	/**
	* @brief	引数付きコンストラクタ
	*/
	MapObjectData(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 rot_, float width_, float height_, float depth_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_),
		m_Width(width_),
		m_Height(height_),
		m_Depth(depth_)
	{}

	D3DXVECTOR3 m_Pos;		//! 座標
	D3DXVECTOR3 m_Scale;	//! スケール
	D3DXVECTOR3 m_Rot;		//! 回転
	float	    m_Width;	//! 横幅
	float	    m_Height;	//! 縦幅
	float	    m_Depth;	//! 奥

};

class MapObject : public ObjectBase
{
public:
	MapObject(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
		ObjectBase(pos_, key_),
		m_MapObjectDataList(mapObjcectList_)
	{}
	virtual ~MapObject() {}

	void CoordinateUpdate(MapData::MapObjectList mapObjId_)
	{
		MapDataBank hoge;
		hoge.Load();
		m_MapObjectDataList = *hoge.GetMapObjectData(mapObjId_);
	}

protected:
	std::vector<MapObjectData> m_MapObjectDataList;
		 

};

#endif