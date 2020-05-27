#include "ObjectManager.h"
#include "../ObjectBase/Character/EnemyBase/Ebiten/Ebiten.h"
#include "../ObjectBase/Character/EnemyBase/Ikaten/Ikaten.h"
#include "../ObjectBase/Character/EnemyBase/Kabochaten/Kabochaten.h"
#include "../ObjectBase/Character/EnemyBase/Sitaketen/Sitaketen.h"
#include "../ObjectBase/Character/EnemyBase/Tikuwaten/Tikuwaten.h"

#include "../ObjectBase/Character/Player/Player.h"

#include "../ObjectBase/MapObject/Barrel/Barrel.h"
#include "../ObjectBase/MapObject/Floor/Floor.h"
#include "../ObjectBase/MapObject/Gate/Gate.h"
#include "../ObjectBase/MapObject/Merrygoland/Merrygoland.h"
#include "../ObjectBase/MapObject/Mountain/Mountain.h"
#include "../ObjectBase/MapObject/Skydome/Skydome.h"
#include "../ObjectBase/MapObject/Tent/Tent.h"
#include "../ObjectBase/MapObject/Vending_Machine/Vending_Machine_Blue.h"
#include "../ObjectBase/MapObject/Vending_Machine/Vending_Machine_Red.h"
#include "../ObjectBase/MapObject/Wall/Wall.h"
#include "../ObjectBase/MapObject/Tree/Tree.h"
#include "../ObjectBase/MapObject/Sapling_Big/SaplingBig.h"
#include "../ObjectBase/MapObject/Sapling_Small/SaplingSmall.h"
#include "../ObjectBase/MapObject/Ferris_Wheel/FerrisWheel.h"
#include "../ObjectBase/MapObject/Shrimp_Statue/ShrimpStatue.h"

Objectmanager::Objectmanager()
{
	m_MapDataBank.Load();

	m_PlayerGroup.push_back(new Player(D3DXVECTOR3(0.0f, 0.0f, 400.0f), "Player"));

	//m_Object.push_back(new Ebiten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Ebiten"));
	//m_Object.push_back(new Ikaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Ikaten"));
	//m_Object.push_back(new Kabochaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Kabochaten"));
	//m_Object.push_back(new Sitaketen(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Sitaketen"));
	//m_Object.push_back(new Tikuwaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Tikuwaten"));

	m_MapObjectGroup.push_back(new Barrel(D3DXVECTOR3(0.0f, 0.0f, 300.0f), "Barrel", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Barrel)));
	m_MapObjectGroup.push_back(new Tent(D3DXVECTOR3(300.0f, 0.0f, 600.0f), "Tent", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Tent)));
	m_MapObjectGroup.push_back(new VendingMachineBlue(D3DXVECTOR3(0.0f, 0.0f, -100.0f), "VendingMachineBlue", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Vending_Machine)));
	//m_MapObjectGroup.push_back(new VendingMachineRed(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "VendingMachineRed"));
	m_MapObjectGroup.push_back(new Wall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Wall", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Wall)));

	m_Object.push_back(new Tree(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Tree", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Tree)));
	m_Object.push_back(new SaplingBig(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SaplingBig", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Sapling_Big)));
	m_Object.push_back(new SaplingSmall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SaplingSmall", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Sapling_Small)));
	m_Object.push_back(new FerrisWheel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "FerrisWheel", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Ferris_Wheel)));
	m_Object.push_back(new ShrimpStatue(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "ShrimpStatue", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Shrimp_Statue)));

	m_Object.push_back(new Floor(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Floor", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Floor)));
	m_Object.push_back(new Gate(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Gate", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Gate)));
	m_Object.push_back(new Merrygoland(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Merrygoland", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Merrygoland)));
	m_Object.push_back(new Mountain(D3DXVECTOR3(0.0f, -400.0f, 0.0f), "Mountain", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Mountain)));
	m_Object.push_back(new Skydome(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SkyDome", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Skydome)));


	m_Camera = new Camera();
}

Objectmanager::~Objectmanager()
{
	AllRelease();
}

void Objectmanager::Update()
{
	for (const auto& itr : m_PlayerGroup)
	{
		itr->Update();
	}

	for (const auto& itr : m_EnemyGroup)
	{
		itr->Update();
	}

	for (const auto& itr : m_MapObjectGroup)
	{
		itr->Update();
	}

	for (const auto& itr : m_Object)
	{
		itr->Update();
	}

	m_Camera->Update();
}

void Objectmanager::Draw()
{
	for (const auto& itr : m_PlayerGroup)
	{
		itr->Draw();
	}

	for (const auto& itr : m_EnemyGroup)
	{
		itr->Draw();
	}

	for (const auto& itr : m_MapObjectGroup)
	{
		itr->Draw();
	}

	for (const auto& itr : m_Object)
	{
		itr->Draw();
	}

}

bool Objectmanager::HitPlayerAndMapObject()
{
	for (auto& itr : m_MapObjectGroup) {

		if (m_Collision.Test(*m_PlayerGroup[0]->GetShape(), *itr->GetShape()) == true)
		{
			return true;
		}
	}

	return false;
}

bool Objectmanager::HitPlayerAndEnemy()
{
	for (auto& itr : m_EnemyGroup) {
		if (m_Collision.Test(*m_PlayerGroup[0]->GetShape(), *itr->GetShape()) == true)
		{
			return true;
		}
	}

	return false;
}

void Objectmanager::AllRelease()
{
	for (auto& itr : m_PlayerGroup) {
		delete itr;
		itr = nullptr;
	}
	m_PlayerGroup.clear();

	for (auto& itr : m_EnemyGroup) {
		delete itr;
		itr = nullptr;
	}
	m_EnemyGroup.clear();

	for (auto& itr : m_MapObjectGroup) {
		delete itr;
		itr = nullptr;
	}
	m_MapObjectGroup.clear();


	delete m_Camera;
	m_Camera = nullptr;
}