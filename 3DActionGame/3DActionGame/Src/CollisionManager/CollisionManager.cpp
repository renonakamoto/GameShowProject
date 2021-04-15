#include "CollisionManager.h"

void CollisionManager::Register(Object3D* object_)
{
	m_Collision3DList.push_back(object_);
}

bool CollisionManager::CheckHitTest(Shape3D& shape_, Object3D* hitObject_)
{
	for (auto* object : m_Collision3DList)
	{
		Shape3D* shape = object->GetShape();
		if (shape) {
			if (shape->HitTest(shape_) == true)
			{
				if (hitObject_) {
					hitObject_ = object;
					return true;
				}
			}
		}
	}
	
	return false;
}

bool CollisionManager::CheckHitObject(Shape3D& shape_, Object3D* hitObject_)
{
	for (auto* object : m_Collision3DList)
	{
		Shape3D* shape = object->GetShape();
		if (shape) {
			if (shape->HitTest(shape_) == true)
			{
				if (hitObject_) {
					hitObject_ = object;
					return true;
				}
			}
		}
	}

	return false;
}

bool CollisionManager::CheckHitObjects(Shape3D& shape_, std::vector<Object3D*>* hitObjects_)
{
	std::vector<Object3D*> tmp;

	for (auto* object : m_Collision3DList)
	{
		Shape3D* shape = object->GetShape();
		if (shape) {
			if (shape->HitTest(shape_) == true)
			{
				tmp.push_back(object);
			}
		}
	}

	if (hitObjects_) {
		for (auto* object : tmp)
		{
			hitObjects_->push_back(object);
		}
	}

	return !tmp.empty();
}

void CollisionManager::Release(Object3D* object_)
{
	if (!object_)return;
	for (auto itr = std::begin(m_Collision3DList); itr != std::end(m_Collision3DList); ++itr)
	{
		if (*itr == object_) {
			m_Collision3DList.erase(itr);
			break;
		}
	}
}

void CollisionManager::AllRelease()
{
	m_Collision3DList.clear();
	m_Collision3DList.shrink_to_fit();
}
