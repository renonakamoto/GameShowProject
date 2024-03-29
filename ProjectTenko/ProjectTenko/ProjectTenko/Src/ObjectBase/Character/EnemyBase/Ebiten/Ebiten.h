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
	*@biref 巡回状態の移動処理関数
	*/
	void Patrol() override;

	/**
	* @biref 巡回中の方向転換処理関数
	*/
	void Turn() override;

private:
	FbxMotion<EbitenMotionList> m_Motion;
};

#endif