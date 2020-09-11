#ifndef EBITEN_H_
#define EBITEN_H_

#include "../EnemyBase.h"

enum class EbitenMotionList
{
	Wait,
};

class Ebiten : public Enemybase
{
public:
	Ebiten(D3DXVECTOR3 pos_, const ObjectBase* 
		_, std::string key_);

	~Ebiten() {}

	virtual void Update() override;
	virtual void Draw() override;

private:
	/**
	*@biref �����Ԃ̈ړ������֐�
	*/
	void Patrol() override;

	/**
	* @biref ���񒆂̕����]�������֐�
	*/
	void Turn() override;

private:
	FbxMotion<EbitenMotionList> m_Motion;
};

#endif