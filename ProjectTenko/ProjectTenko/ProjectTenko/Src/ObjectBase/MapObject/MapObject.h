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
	template<typename... KeyList>
	MapObject(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList) :
		m_MapObjectDataList(mapObjcectList_)
	{
		Develop(keyList...);
	}

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
		m_MapObjectDataList = hoge.GetMapObjectData(mapObjId_);
	}

protected:
	std::vector<MapObjectData>* m_MapObjectDataList;
	//! ワールド行列
	std::vector<D3DXMATRIX> m_MatWorld;
	//! Fbxデータのキー
	std::vector<std::string> m_FbxKeys;
		 

private:
	template<typename First, typename... Rest>
	void Develop(const First& first_, const Rest&... rest_)
	{
		m_FbxKeys.push_back(first_);
		Develop(rest_...);
	}

	//! 無限ループにならないように
	void Develop() { return; }

};

#endif