#include "ObjectManager.h"
#include "../Engine/Input/InputManager.h"
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
#include "../ObjectBase/MapObject/Vending_Machine/Vending_Machine.h"
#include "../ObjectBase/MapObject/Wall/Wall.h"
#include "../ObjectBase/MapObject/Tree/Tree.h"
#include "../ObjectBase/MapObject/Sapling_Big/SaplingBig.h"
#include "../ObjectBase/MapObject/Sapling_Small/SaplingSmall.h"
#include "../ObjectBase/MapObject/Ferris_Wheel/FerrisWheel.h"
#include "../ObjectBase/MapObject/Shrimp_Statue/ShrimpStatue.h"
#include "../Collision/Shape/Ray.h"
#include "../Collision/Shape/AABB.h"


Objectmanager::Objectmanager()
{
}

Objectmanager::~Objectmanager()
{
	AllRelease();
}

void Objectmanager::JudgementCollition(std::vector<Shape*>* pOut_, const D3DXVECTOR3& basePoint_, float length)
{
	D3DXVECTOR3 base_pos = basePoint_;
	D3DXVECTOR3 base_to_mapobject;



	for (const auto& v : m_MapObjectGroup)
	{
		for (const auto& w : v->GetShape())
		{
			base_to_mapobject = w->GetPos() - base_pos;

			if (D3DXVec3Length(&base_to_mapobject) < length)
			{
				pOut_->push_back(w);
			}
		}
	}
}



void Objectmanager::Update()
{
	if (m_Player) m_Player->Update();

	for (const auto& itr : m_EnemyGroup)
	{
		itr->Update();
	}

	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_R))
	{
		for (const auto& itr : m_MapObjectGroup)
		{
			itr->Update();
		}

		for (const auto& itr : m_Object)
		{
			itr->Update();
		}
	}

	if (m_Camera) m_Camera->Update();
}

void Objectmanager::Draw()
{
	if (m_Player) m_Player->Draw();

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


	D3DXMATRIX mat_world, mat_Scale;
	D3DXMatrixIdentity(&mat_world);
	D3DXMatrixScaling(&mat_Scale, 4.f, 4.f, 4.f);
	D3DXMatrixTranslation(&mat_world, -810.0f, 0.0f, 1.0f);

	mat_world = mat_Scale * mat_world;

	THE_FBXMANAGER->Draw("Box", mat_world);
}

void Objectmanager::EntryObject(ObjectType type_)
{
	switch (type_)
	{
	case Objectmanager::ObjectType::Player:
		this->CreatePlayer();
		break;

	case Objectmanager::ObjectType::Enemy:
		this->CreateEnemies();
		break;

	case Objectmanager::ObjectType::Camera:
		if (m_Camera)return;
		m_Camera = new Camera();

	case Objectmanager::ObjectType::MapObject:
		this->CreateMap();
		break;

	default:
		break;
	}

}

void Objectmanager::ExitObject(ObjectType type_)
{
	switch (type_)
	{
	case Objectmanager::ObjectType::Player:
		if (!m_Player) return;
		delete m_Player;
		m_Player = nullptr;
		break;

	case Objectmanager::ObjectType::Enemy:
		if (m_EnemyGroup.empty()) return;
		for (auto itr = std::begin(m_EnemyGroup); itr != std::end(m_EnemyGroup); ++itr)
		{
			delete* itr;
			*itr = nullptr;
		}
		m_EnemyGroup.clear();
		break;

	case Objectmanager::ObjectType::Camera:
		if (!m_Camera) return;
		delete m_Camera;
		m_Camera = nullptr;
		break;

	case Objectmanager::ObjectType::MapObject:
		if (m_MapObjectGroup.empty() || m_Object.empty()) return;

		for (auto itr = std::begin(m_MapObjectGroup); itr != std::end(m_MapObjectGroup); ++itr)
		{
			delete* itr;
			*itr = nullptr;
		}
		m_MapObjectGroup.clear();

		for (auto itr = std::begin(m_Object); itr != std::end(m_Object); ++itr)
		{
			delete* itr;
			*itr = nullptr;
		}
		m_Object.clear();

		break;
	default:
		break;
	}
}

bool Objectmanager::HitPlayerAndMapObject()
{
	std::vector<Shape*> collition_list;
	JudgementCollition(&collition_list, m_Player->GetPos(), 500.0f);

	if (m_Collision.Test(m_Player->GetShape(), collition_list) == true)
	{
		return true;
	}

	return false;
}

bool Objectmanager::HitPlayerAndEnemy()
{
	for (const auto& itr : m_EnemyGroup) {
		if (m_Collision.Test(m_Player->GetShape(), itr->GetShape()) == true)
		{
			return true;
		}
	}

	return false;
}

bool Objectmanager::HitCameraAndObject()
{
	std::vector<Shape*> tmp_camera_shape;
	tmp_camera_shape.push_back(m_Camera->GetShape());
	for (auto& itr : m_MapObjectGroup) {
		if (m_Collision.Test(tmp_camera_shape, itr->GetShape()) == true)
		{
			return true;
		}
	}

	return false;
}

bool Objectmanager::HitRayAndObject(const D3DXVECTOR3& origin_, const D3DXVECTOR3& delta_)
{
	std::vector<Shape*> tmp_ray;
	tmp_ray.push_back(new Ray(origin_, delta_));

	for (auto& itr : m_MapObjectGroup) {
		if (m_Collision.Test(tmp_ray, itr->GetShape()) == true)
		{
			return true;
		}
	}

	return false;
}

bool Objectmanager::HitPlayerAndClearTrigger()
{
	std::vector<Shape*> hoge;
	hoge.push_back(new AABBShape(D3DXVECTOR3(1413.0f, 0.0f, -260.0f), 89.0f, 89.0f, 89.0f));

	if (m_Collision.Test(m_Player->GetShape(), hoge) == true) {
		return true;
	}

	return false;
}

void Objectmanager::AllRelease()
{
	for(size_t i = static_cast<int>(ObjectType::Player); i <= static_cast<int>(ObjectType::MapObject); ++i)
	{ 
		ExitObject(static_cast<ObjectType>(i));
	}
	delete m_Camera;
	m_Camera = nullptr;
}

void Objectmanager::CreatePlayer()
{
	if (m_Player) return;
	m_Player = new Player(D3DXVECTOR3(-810.0f, 0.0f, 1.0f), "Player");
}

void Objectmanager::CreateEnemies()
{
	if (!m_EnemyGroup.empty()) return;

	//m_Object.push_back(new Ebiten(D3DXVECTOR3(0.0f, 0.0f, 0.0f),	 m_Player, "Ebiten"));
	//m_Object.push_back(new Ikaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f),	 m_Player, "Ikaten"));
	//m_Object.push_back(new Kabochaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Player, "Kabochaten"));
	//m_Object.push_back(new Sitaketen(D3DXVECTOR3(0.0f, 0.0f, 0.0f),  m_Player, "Sitaketen"));
	//m_Object.push_back(new Tikuwaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f),  m_Player, "Tikuwaten"));
}

void Objectmanager::CreateMap()
{
	if (!m_MapObjectGroup.empty() || !m_Object.empty()) return;

	m_MapDataBank.Load();
	m_MapObjectGroup.push_back(new Barrel(D3DXVECTOR3(0.0f, 0.0f, 300.0f), "Barrel", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Barrel)));
	m_MapObjectGroup.push_back(new Tent(D3DXVECTOR3(300.0f, 0.0f, 600.0f), "Tent", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Tent)));
	m_MapObjectGroup.push_back(new VendingMachine(D3DXVECTOR3(0.0f, 0.0f, -100.0f), "VendingMachineBlue", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Vending_Machine)));
	m_MapObjectGroup.push_back(new Wall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Wall", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Wall)));
	m_MapObjectGroup.push_back(new Tree(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Tree", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Tree)));
	m_MapObjectGroup.push_back(new SaplingBig(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SaplingBig", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Sapling_Big)));
	m_MapObjectGroup.push_back(new SaplingSmall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SaplingSmall", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Sapling_Small)));
	m_MapObjectGroup.push_back(new FerrisWheel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "FerrisWheel", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Ferris_Wheel)));
	m_MapObjectGroup.push_back(new ShrimpStatue(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "ShrimpStatue", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Shrimp_Statue)));
	m_MapObjectGroup.push_back(new Merrygoland(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Merrygoland", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Merrygoland)));
	m_MapObjectGroup.push_back(new Gate(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Gate", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Gate)));

	m_Object.push_back(new Floor(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Floor", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Floor)));
	m_Object.push_back(new Mountain(D3DXVECTOR3(0.0f, -400.0f, 0.0f), "Mountain", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Mountain)));
	m_Object.push_back(new Skydome(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "SkyDome", *m_MapDataBank.GetMapObjectData(MapData::MapObjectList::Skydome)));
}