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
		m_Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{}

	/**
	* @brief	引数付きコンストラクタ
	*/
	MapObjectData(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 rot_, float width_, float height_, float depth_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_)
	{}

	D3DXVECTOR3 m_Pos;		//! 座標
	D3DXVECTOR3 m_Scale;	//! スケール
	D3DXVECTOR3 m_Rot;		//! 回転

};

class MapObject : public ObjectBase
{
public:

	/**
	* @brief 引数付きコンストラクタ
	*/
	MapObject(D3DXVECTOR3 pos_, std::string key_, std::vector<MapObjectData> mapObjcectList_) :
		ObjectBase(pos_, key_),
		m_MapObjectDataList(mapObjcectList_)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~MapObject() {}

	// 再読み込み
	void CoordinateUpdate(MapData::MapObjectList mapObjId_)
	{
		//TODO MapDataBankをシングルトン
		MapDataBank hoge;
		hoge.Load();
		m_MapObjectDataList = *hoge.GetMapObjectData(mapObjId_);
	}

protected:
	std::vector<MapObjectData> m_MapObjectDataList;
		 
};

#endif