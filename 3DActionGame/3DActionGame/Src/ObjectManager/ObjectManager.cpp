#include "ObjectManager.h"

void ObjectManager::Update()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i])m_Objects[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i])m_Objects[i]->Draw();
	}
}

void ObjectManager::Register(ObjectBase* object_)
{
	m_Objects.push_back(object_);
}

void ObjectManager::Release(ObjectBase* object_)
{
	if (!object_)return;
	for (auto itr = std::begin(m_Objects); itr != std::end(m_Objects); ++itr)
	{
		if (*itr == object_) {
			m_Objects.erase(itr);
			m_Objects.shrink_to_fit();
			delete object_;
			object_ = nullptr;
			break;
		}
	}
}

ObjectBase* ObjectManager::GetObj(std::string tag_)
{
	for (auto* objects : m_Objects)
	{
		if (objects->GetTag() == tag_)
		{
			return objects;
		}
	}

	return nullptr;
}

void ObjectManager::AllRelease()
{
	for (ObjectBase* object : m_Objects)
	{
		delete object;
		object = nullptr;
	}

	m_Objects.clear();
	m_Objects.shrink_to_fit();
}
