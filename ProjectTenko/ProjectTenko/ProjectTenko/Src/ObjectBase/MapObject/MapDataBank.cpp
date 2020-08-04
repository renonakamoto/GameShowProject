#include "MapDataBank.h"
#include "../../ExternalFle/Csv/Csv.h"
#include "../MapObject/MapObject.h"

template<typename out, typename in> inline out scast(in value_) { return static_cast<out>(value_); }

bool MapDataBank::Load()
{
	using namespace MapData;

	std::string file_name = "assets/Csv/MapData.csv";
	std::vector < std::vector < std::string >> map_table;
	bool status = false;

	// 読み込んだデータをmap_tableに保存
	status = Csv::Load(file_name, map_table);

	// 読み込みに失敗
	if (!status) { return false; }
	

	MapObjectData data;
	// CSVの一行目は無視する
	for (int i = 1; i < map_table.size(); i++)
	{
		// 空白の場合
		if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "") { continue; }
		
		// 文字列を数値に変換し格納する
		data.m_Pos.x   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::PosX)]);
		data.m_Pos.y   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::PosY)]);
		data.m_Pos.z   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::PosZ)]);
		data.m_Rot.x   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::RotX)]);
		data.m_Rot.y   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::RotY)]);
		data.m_Rot.z   = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::RotZ)]);
		data.m_Scale.x = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ScalX)]);
		data.m_Scale.y = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ScalY)]);
		data.m_Scale.z = std::stof(map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ScalZ)]);

		// データごとに振り分ける
		if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Barrel")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Barrel)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Floor")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Floor)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Gate")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Gate)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "MerryGoland")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Merrygoland)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Mountain")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Mountain)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Skydome")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Skydome)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Tent")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Tent)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Vending_Machine")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Vending_Machine)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Wall")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Wall)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Tree")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Tree)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Sapling_Small")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Sapling_Small)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Sapling_Big")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Sapling_Big)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Ferris_Wheel")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Ferris_Wheel)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "Shrimp_Statue")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::Shrimp_Statue)].push_back(data);
		}
		else if (map_table[i][scast<int, MapObjectDataList>(MapObjectDataList::ObjectName)] == "StreetLamp")
		{
			m_MapObjectDataList[scast<int, MapObjectList>(MapObjectList::StreetLamp)].push_back(data);
		}

	}

	return true;
}