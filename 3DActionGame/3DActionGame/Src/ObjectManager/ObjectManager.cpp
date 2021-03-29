#include "ObjectManager.h"

void ObjectManager::Update()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Draw();
	}
}

void ObjectManager::Register(ObjectBase* object_)
{
	m_Objects.push_back(object_);
}

void ObjectManager::Release()
{
	for (auto object : m_Objects)
	{
		delete object;
		object = nullptr;
	}
}
