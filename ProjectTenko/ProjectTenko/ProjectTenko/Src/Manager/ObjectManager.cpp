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

Objectmanager::Objectmanager()
{
	m_Object.push_back(new Ebiten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Ebiten"));
	m_Object.push_back(new Ikaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Ikaten"));
	m_Object.push_back(new Kabochaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Kabochaten"));
	m_Object.push_back(new Sitaketen(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Sitaketen"));
	m_Object.push_back(new Tikuwaten(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Tikuwaten"));

	m_Object.push_back(new Player(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Player"));

	m_Object.push_back(new Barrel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Barrel"));
	m_Object.push_back(new Floor(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Floor"));
	m_Object.push_back(new Gate(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Gate"));
	m_Object.push_back(new Merrygoland(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "merrygoland_Foundation"));
	m_Object.push_back(new Mountain(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Mountain"));
	m_Object.push_back(new Skydome(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Skydome"));
	m_Object.push_back(new Tent(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Tent"));
	m_Object.push_back(new VendingMachineBlue(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "VendingMachineBlue"));
	m_Object.push_back(new VendingMachineRed(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "VendingMachineRed"));
	m_Object.push_back(new Wall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Wall"));
}

Objectmanager::~Objectmanager()
{
	m_Object.clear();
}

void Objectmanager::Update()
{
	for (const auto& itr : m_Object)
	{
		itr->Update();
	}
}

void Objectmanager::Draw()
{
	for (const auto& itr : m_Object)
	{
		itr->Draw();
	}
}
