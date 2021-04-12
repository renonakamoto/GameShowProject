#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/FbxStorage.h"
#include "../Stage/Stage.h"

class Enemy : public Object3D
{
public:
	Enemy(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_),
		m_Model(nullptr),
		m_Stage(nullptr)
	{
		Init();
	}

	~Enemy()
	{
		Release();
	}

	void Update()override;
	void Draw()override;
private:
	void Init() override;
	void Release()override;

private:
	FbxModel* m_Model;
	Stage* m_Stage;

};

#endif
