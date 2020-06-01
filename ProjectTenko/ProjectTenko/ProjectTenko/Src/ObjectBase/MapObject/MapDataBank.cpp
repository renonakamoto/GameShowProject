#include "MapDataBank.h"
#include "../../ExternalFle/Csv/Csv.h"
#include "../MapObject/MapObject.h"

bool MapDataBank::Load()
{
	bool status = false;
	std::string file_name = "assets/Csv/MapData.csv";
	std::vector < std::vector < std::string >> map_table;

	status = Csv::Load(file_name, map_table);
	if (!status) { return false; }

	MapObjectData data;
	for (int i = 1; i < map_table.size(); i++)
	{
		if (map_table[i][MapData::MapObjectDataList::ObjectName] == "") { continue; }
		data.m_Pos.x = std::stof(map_table[i][MapData::MapObjectDataList::PosX]);
		data.m_Pos.y = std::stof(map_table[i][MapData::MapObjectDataList::PosY]);
		data.m_Pos.z = std::stof(map_table[i][MapData::MapObjectDataList::PosZ]);
		data.m_Rot.x = std::stof(map_table[i][MapData::MapObjectDataList::RotX]);
		data.m_Rot.y = std::stof(map_table[i][MapData::MapObjectDataList::RotY]);
		data.m_Rot.z = std::stof(map_table[i][MapData::MapObjectDataList::RotZ]);
		data.m_Scale.x = std::stof(map_table[i][MapData::MapObjectDataList::ScalX]);
		data.m_Scale.y = std::stof(map_table[i][MapData::MapObjectDataList::ScalY]);
		data.m_Scale.z = std::stof(map_table[i][MapData::MapObjectDataList::ScalZ]);

		if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Barrel")
		{
			m_MapObjectDataList[MapData::MapObjectList::Barrel].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Floor")
		{
			m_MapObjectDataList[MapData::MapObjectList::Floor].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Gate")
		{
			m_MapObjectDataList[MapData::MapObjectList::Gate].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "MerryGoland")
		{
			m_MapObjectDataList[MapData::MapObjectList::Merrygoland].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Mountain")
		{
			m_MapObjectDataList[MapData::MapObjectList::Mountain].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Skydome")
		{
			m_MapObjectDataList[MapData::MapObjectList::Skydome].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Tent")
		{
			m_MapObjectDataList[MapData::MapObjectList::Tent].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Vending_Machine")
		{
			m_MapObjectDataList[MapData::MapObjectList::Vending_Machine].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Wall")
		{
			m_MapObjectDataList[MapData::MapObjectList::Wall].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Tree")
		{
			m_MapObjectDataList[MapData::MapObjectList::Tree].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Sapling_Small")
		{
			m_MapObjectDataList[MapData::MapObjectList::Sapling_Small].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Sapling_Big")
		{
			m_MapObjectDataList[MapData::MapObjectList::Sapling_Big].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Ferris_Wheel")
		{
			m_MapObjectDataList[MapData::MapObjectList::Ferris_Wheel].push_back(data);
		}
		else if (map_table[i][MapData::MapObjectDataList::ObjectName] == "Shrimp_Statue")
		{
			m_MapObjectDataList[MapData::MapObjectList::Shrimp_Statue].push_back(data);
		}

	}

	return true;
}

std::vector<MapObjectData>* MapDataBank::GetMapObjectData(MapData::MapObjectList objectId_)
{
	return &m_MapObjectDataList[objectId_];
}
