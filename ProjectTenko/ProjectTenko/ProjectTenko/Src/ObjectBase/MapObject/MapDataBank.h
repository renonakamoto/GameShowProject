#ifndef MAPDATABANK_H_
#define MAPDATABANK_H_

#include <string>
#include <vector>

class MapObjectData;

namespace MapData
{
	/**
	* @brief   マップオブジェクトの種類
	*/
	enum class MapObjectList
	{
		Barrel,				//! 樽
		Floor,				//! 床
		Gate,				//! ゲート
		Merrygoland,		//! メリーゴーランド
		Mountain,			//! 山
		Skydome,			//!	スカイドーム
		Tent,				//!	テント
		Vending_Machine,	//!	自販機
		Wall,				//!	壁
		Tree,				//!	木
		Sapling_Small,		//!	苗木(小)
		Sapling_Big,		//! 苗木(大)
		Ferris_Wheel,		//!	観覧車
		Shrimp_Statue,		//!	海老天の像

		MaxMapObject,		//! 種類の数
	};

	/**
	* @brief   マップオブジェクトのデータリスト
	*/
	enum class MapObjectDataList
	{
		ObjectName,	//! オブジェクトの名前

		PosX,		//! X座標
		PosY,		//! Y座標
		PosZ,		//! Z座標

		ScalX,		//! Xスケール
		ScalY,		//!	Yスケール
		ScalZ,		//!	Zスケール

		RotX,		//!	X軸回転
		RotY,		//!	Y軸回転
		RotZ,		//!	Z軸回転
	};
}

/**
* @brief   マップオブジェクトのデータを扱うクラス
* @details マップオブジェクトのデータをCSVから読み込み変換する
*/
class MapDataBank
{
public:
	/**
	* @brief Csvからマップデータを読み込む
	* @return bool 成功:true 失敗:false
	*/
	bool Load();

	/**
	* @brief マップのデータを返す関数
	* @param[in] objectId_ オブジェクトの種類
	* @return std::vector<MapObjectData>* マップオブジェクトデータ
	*/
	std::vector<MapObjectData>* GetMapObjectData(MapData::MapObjectList objectId_)
	{
		return &m_MapObjectDataList[static_cast<int>(objectId_)];
	}

private:
	//!	外部から読み込んだマップオブジェクトのデータを保存する変数
	std::vector<MapObjectData> m_MapObjectDataList[static_cast<int>(MapData::MapObjectList::MaxMapObject)];

};

#endif