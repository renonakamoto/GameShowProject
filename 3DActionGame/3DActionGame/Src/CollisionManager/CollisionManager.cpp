#include "CollisionManager.h"

void CollisionManager::Register(Object3D* object_)
{
	if (object_->GetShape() == nullptr) return;
	// 登録
	m_Collision3DList.push_back(object_);
}

bool CollisionManager::CheckHitObject(Shape3D& shape_, Object3D* hitObject_)
{
	for (Object3D* object : m_Collision3DList)
	{
		// 形状を取得
		Shape3D* shape = object->GetShape();
		// nullチェック
		if (shape == nullptr) continue;
		
		// 判定
		if (shape->HitTest(shape_) == true)
		{
			if (hitObject_) hitObject_ = object;
			return true;
		}
	}

	return false;
}

bool CollisionManager::CheckHitObjects(Shape3D& shape_, std::vector<Object3D*>* hitObjects_)
{
	bool hit = false;

	for (auto* object : m_Collision3DList)
	{
		// 形状を取得
		Shape3D* shape = object->GetShape();
		// nullチェック
		if (shape == nullptr) continue;
		
		// 判定
		if (shape->HitTest(shape_) == true)
		{
			hit = true;
			if (hitObjects_) hitObjects_->push_back(object);
		}
		
	}

	return hit;
}

void CollisionManager::Release(Object3D* object_)
{
	if (!object_)return;
	for (auto itr = std::begin(m_Collision3DList); itr != std::end(m_Collision3DList); ++itr)
	{
		// 同じオブジェクトの場合削除
		if (*itr == object_) {
			m_Collision3DList.erase(itr);
			// 領域を切り詰める
			m_Collision3DList.shrink_to_fit();
			break;
		}
	}
}

void CollisionManager::AllRelease()
{
	if (m_Collision3DList.empty()) return;
	// 要素を全削除
	m_Collision3DList.clear();
	// 領域を切り詰める
	m_Collision3DList.shrink_to_fit();
}
