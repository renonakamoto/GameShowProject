#ifndef SWORD_H_
#define SWORD_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "../../Shape/3D/AABB/ShapeAABB.h"

class Sword : public Object3D
{
public:
	Sword()
	{}

	~Sword()
	{}
	
	//void Update()override;
	//void Draw()override;
	
private:
	//void Init() override;
	//void Release()override;
	
private:
	FbxModel* m_Model;
	ShapeAABB m_AABB;

};

#endif