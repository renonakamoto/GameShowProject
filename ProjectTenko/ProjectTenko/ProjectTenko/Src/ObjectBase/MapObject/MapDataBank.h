#ifndef MAPDATABANK_H_
#define MAPDATABANK_H_

#include <string>
#include <vector>

class MapObjectData;

namespace MapData
{
	enum MapObjectList
	{
		Barrel,
		Floor,
		Gate,
		Merrygoland,
		Mountain,
		Skydome,
		Tent,
		Vending_Machine,
		Wall,
		Tree,
		Sapling_Small,
		Sapling_Big,
		Ferris_Wheel,
		Shrimp_Statue,

		MAXMapObject,
	};

	enum MapObjectDataList
	{
		ObjectName,

		PosX,
		PosY,
		PosZ,

		ScalX,
		ScalY,
		ScalZ,

		RotX,
		RotY,
		RotZ,

		Width,
		Height,
		Depth,
	};
}

class MapDataBank
{
public:
	bool Load();

	std::vector<MapObjectData>* GetMapObjectData(MapData::MapObjectList objectId_);

private:
	std::vector<MapObjectData> m_MapObjectDataList[MapData::MAXMapObject];

};

#endif