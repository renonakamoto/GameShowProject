#include "ObjectManager.h"

void ObjectManager::Init()
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i])m_ObjectList[i]->Init();
	}
	for (size_t i = 0; i < m_ShadowMapObjectList.size(); ++i)
	{
		if (m_ShadowMapObjectList[i])m_ShadowMapObjectList[i]->Init();
	}
}

void ObjectManager::Update()
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i])m_ObjectList[i]->Update();
	}
	for (size_t i = 0; i < m_ShadowMapObjectList.size(); ++i)
	{
		if (m_ShadowMapObjectList[i])m_ShadowMapObjectList[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i])m_ObjectList[i]->Draw();
	}
	for (size_t i = 0; i < m_ShadowMapObjectList.size(); ++i)
	{
		if (m_ShadowMapObjectList[i])m_ShadowMapObjectList[i]->Draw();
	}
}

void ObjectManager::DrawShadowMapObj()
{
	for (size_t i = 0; i < m_ShadowMapObjectList.size(); ++i)
	{
		if (m_ShadowMapObjectList[i])m_ShadowMapObjectList[i]->DrawShadowMap();
	}
}

void ObjectManager::Register(ObjectBase* object_)
{
	if (object_ == nullptr) return;
	m_ObjectList.push_back(object_);
}

void ObjectManager::ResisterShadowMap(ShadowMapObject* object_)
{
	if (object_ == nullptr) return;
	m_ShadowMapObjectList.push_back(object_);
}

void ObjectManager::Release(ObjectBase* object_)
{
	if (!object_ || m_ObjectList.empty())return;
	for (auto itr = std::begin(m_ObjectList); itr != std::end(m_ObjectList); ++itr)
	{
		if (*itr == object_) {
			// リストから削除
			m_ObjectList.erase(itr);
			// 領域を切り詰める
			m_ObjectList.shrink_to_fit();
			// 解放する
			delete object_;
			object_ = nullptr;
			
			break;
		}
	}
}

void ObjectManager::Release(ShadowMapObject* object_)
{
	if (!object_ || m_ShadowMapObjectList.empty())return;
	for (auto itr = std::begin(m_ShadowMapObjectList); itr != std::end(m_ShadowMapObjectList); ++itr)
	{
		if (*itr == object_) {
			// リストから削除
			m_ShadowMapObjectList.erase(itr);
			// 領域を切り詰める
			m_ShadowMapObjectList.shrink_to_fit();
			// 解放する
			delete object_;
			object_ = nullptr;

			break;
		}
	}
}

ObjectBase* ObjectManager::GetObj(std::string tag_)
{
	for (auto* object : m_ObjectList)
	{
		if (object->GetTag() == tag_)
		{
			return object;
		}
	}

	for (auto* object : m_ShadowMapObjectList)
	{
		if (object->GetTag() == tag_)
		{
			return object;
		}
	}


	return nullptr;
}

void ObjectManager::AllRelease()
{
	if (m_ObjectList.empty()) return;
	for (ObjectBase* object : m_ObjectList)
	{
		delete object;
		object = nullptr;
	}

	m_ObjectList.clear();
	// 領域を切り詰める
	m_ObjectList.shrink_to_fit();

	if (m_ShadowMapObjectList.empty()) return;
	for (ObjectBase* object : m_ShadowMapObjectList)
	{
		delete object;
		object = nullptr;
	}

	m_ShadowMapObjectList.clear();
	// 領域を切り詰める
	m_ShadowMapObjectList.shrink_to_fit();

}
