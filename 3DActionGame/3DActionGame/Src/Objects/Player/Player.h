#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"

class Player : public Object3D
{
public:
	Player() :
		m_Model(nullptr)
	{
		Init();
	}
	~Player(){}

	
	void Update()override;
	void Draw()override;

private:
	void Init() override;
	void Release()override;

private:
	FbxModel* m_Model;

};

#endif